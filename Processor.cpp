#include "Processor.hpp"
#include "message_t.hpp"

#include <thread>
#include <signal.h>

namespace ProcessorNS {
std::atomic<bool> can_work(true);
    
void signal_handler (int signal) {
    can_work.store(false);
    message_t (std::cout)  << "Stopped by signal.";
}
}

void ProcessorNS::Processor::set_stop_signal_handler () {
    struct sigaction act;
    act = {0};
    act.sa_handler = signal_handler;
    sigemptyset(&act.sa_mask);                                                             
    sigaddset(&act.sa_mask, SIGINT); 
    sigaction(SIGINT, &act, 0);
}


ProcessorNS::Processor::Processor(AReceiver& receiver, ASender<float>& sender, unsigned int timeout)
: receiver (receiver), sender (sender) {
    values[PCKG_ID1].canal_id = 1;
    values[PCKG_ID2].canal_id = 2;
    values[PCKG_ID3].canal_id = 3;

    this->timeout = std::chrono::seconds(timeout);
}


ProcessorNS::Processor::~Processor() {
    for (auto& thread : threads)
        thread.join();
    
    message_t (std::cout) << "Stopped";
}



void ProcessorNS::Processor::run() {
    message_t (std::cout) << "Start working.";
    
    set_stop_signal_handler ();
    
    threads = {
        std::thread([&]() {
            receive_data(); }),
        std::thread([&]() {
            data_processing(); })
    };
}


void ProcessorNS::Processor::receive_data() {
    std::vector<char> vec;

    while (can_work) {
        vec = receiver.receive();
        msg_t *msg = (msg_t*) & vec[0];

        if (vec.size() >= sizeof (msg_t)) {
            pack_values(msg);
        } else if (errno == EWOULDBLOCK || errno == EAGAIN) {
            send_error();
            message_t() << "Socket timeout!";
        }
    }
}


void ProcessorNS::Processor::pack_values(msg_t* message) {
    type_t packet;

    packet.msg = *message;
    packet.receive_time = std::chrono::duration_cast<std::chrono::seconds> (std::chrono::system_clock::now().time_since_epoch());

    bool is_valid_ids = PCKG_ID1 <= message->packet_id && message->packet_id <= PCKG_ID3;
    if (is_valid_ids) {
        const std::unique_lock<std::mutex> lock(values_control);
        values[message->packet_id] = packet;
    }
}


void ProcessorNS::Processor::data_processing() {
    while (can_work) {

        std::this_thread::sleep_for(timeout);

        process();
    }

    message_t(std::cout) << "The work is over";
}


void ProcessorNS::Processor::process() {

    std::vector<float> vec = extract_values();
    
    for (auto& val : vec) {
        message_t () << val;
    }
    
    if (vec.empty () == false) {
        message_t (std::cout) << "Vector isn't empty.";
        sender.set_value(calculate_corrected_average(vec));
        sender.send();
    } else {
        message_t() << "Invalid data! " << "Recieved [" << vec.size() << "] messages!";
        send_error();
    }
}


std::vector<float> ProcessorNS::Processor::extract_values () {
    const std::lock_guard<std::mutex> lock(values_control);

    message_t (std::cout) << "Extracting values.";
    
    std::chrono::seconds start_time = std::chrono::duration_cast<std::chrono::seconds> (std::chrono::system_clock::now().time_since_epoch());

    std::vector<float> vec;
    const int VALID_STATE = 0;

    for (auto pair : values) {
        std::chrono::seconds time_differrence = start_time - pair.second.receive_time;

        if (time_differrence < timeout) {
            const bool IS_VALID_MESSAGE = pair.second.msg.element[0].state == VALID_STATE;

            if (IS_VALID_MESSAGE) {
                float value = pair.second.msg.element[0].value;
                message_t (std::cout) << "Added value [" << value << "].";
                vec.push_back(value);
            } else {
                message_t() << '[' << pair.second.canal_id << ']' << " canal invalid state [" << pair.second.msg.element[0].state << ']';
            }

        } else {
            message_t() << '[' << pair.second.canal_id << ']' << " canal timeout [" << time_differrence.count() << ']';
        }
    }
    
    for (auto& value : vec)
        std::cout << value << " ";

    return vec;
}


float ProcessorNS::Processor::get_average(std::vector<float>& vec, size_t deviation_index) {
    float sum = 0;
    int amount = 0;

    for (size_t idx = 0; idx < vec.size(); ++idx) {
        if (idx != deviation_index) {
            ++amount;
            sum += vec[idx];
        }
    }

    return !amount ? 0 : sum / amount;
}


float ProcessorNS::Processor::calculate_corrected_average(std::vector<float>& vec) {
    float average = get_average(vec);

    int current_deviation_index = get_deviation_index(vec, average);

    average = get_average(vec, current_deviation_index);

    return average;
}


int ProcessorNS::Processor::get_deviation_index(std::vector<float> &vec, float average) {
    const float max_deviation_ub = average * 1.15;
    const float max_deviation_lb = average * 0.85;


    int dev_idx = -1;
    float max_deviation = 0;
    for (size_t idx = 0; idx < vec.size(); ++idx) {
        if (vec[idx] > max_deviation_ub || vec[idx] < max_deviation_lb) {
            float cur_deviation = abs(vec[idx] - average);

            if (cur_deviation > max_deviation) {
                max_deviation = cur_deviation;
                dev_idx = idx;
            }

        }
    }

    return dev_idx;
}


void ProcessorNS::Processor::send_error() {
    message_t () << "Trying to send error message.";
    sender.set_value(0.0000f);
    sender.send();
    message_t () << "Error message was sent.";
}