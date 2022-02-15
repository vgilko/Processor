#pragma once

#include "AReceiver.hpp"
#include "ASender.hpp"

#include <atomic>
#include <mutex>
#include <thread>

#include <map>
#include <vector>
#include <array>

enum packets_id_t{
    PCKG_ID1 = 65537,
    PCKG_ID2 = 65538,
    PCKG_ID3 = 65539
};

#pragma pack(push, 1)
struct element_t {
    float value;
    short int state;
};

struct msg_t {
    packets_id_t packet_id;
    element_t element[1];
};
#pragma pack(pop)

struct type_t {
    int canal_id;
    msg_t msg;
    std::chrono::seconds receive_time;
};

namespace ProcessorNS {
class Processor {
public:
    Processor (AReceiver& receiver, ASender<float>& sender, unsigned int timeout = 4);
    virtual ~Processor ();
    
    void run ();

private:
    AReceiver& receiver;
    ASender<float>& sender;

    std::chrono::seconds timeout;

    std::array<std::thread, 2> threads;

    std::map<packets_id_t, type_t> values;
    std::mutex values_control;
    
    void set_stop_signal_handler ();

    void receive_data ();
    void data_processing ();

    void pack_values (msg_t* message);
    void process ();
    std::vector<float> extract_values ();

    float calculate_corrected_average (std::vector<float>& vec);
    float get_average (std::vector<float>& vec, size_t deviation_index = -1);
    int get_deviation_index (std::vector<float>& vec, float average);

    void send_error ();
};
}