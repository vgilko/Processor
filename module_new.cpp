#include <stdio.h>
#include <sstream>
#include <iostream>

#include <string.h>
#include <chrono>
#include <map>
#include <vector>

#include <atomic>
#include <mutex>
#include <thread>

#include <errno.h>

#include <signal.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

#include <fcntl.h>
#include <termios.h>



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

class message_t : public std::stringstream{
public:
    message_t(): stream(std::cerr){}

    message_t(std::ostream &s) : stream(s){}

    ~message_t(){
        stream << this->str() << std::endl;
    }

private:
    std::ostream& stream;
};

std::map<packets_id_t, type_t> values;

std::mutex _mutex;
std::atomic<bool> can_work(true);

const std::chrono::seconds TIMEOUT(4);
const char* PORT_NAME = "/dev/ttyM10";
const char* SERVER = "127.0.0.1";
const int PORT = 65001;
typedef unsigned char uchar;

int com_port_fd;
const char module_id[] = "01";
struct termios old_settings;

const bool WITH_CHKSUM = false;

void get_data_from_socket();
bool init_serial_port (const char*);
void data_processing();
int create_socket(struct sockaddr_in*);
int send_to_module(float fl, bool with_checksum);
std::string to_milli_a(float);
std::string int_to_hex_string(int sum);
int dcon_checksum(std::string&);
void close_com();


void signal_handler(int sig){
    can_work = false;
}

int main(int argc, char const *argv[]){
    std::array<std::thread, 2> threads {{std::thread(get_data_from_socket),
                            std::thread(data_processing)
    }};

    struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = signal_handler;

	sigemptyset(&act.sa_mask);                                                             
	sigaddset(&act.sa_mask, SIGINT); 
	sigaction(SIGINT, &act, 0);

    for (auto &thread : threads){
        thread.join();
    }

    return 0;
}





int send_to_module(float output_value, bool with_checksum = false) {
	std::string dcon_req = "#";
	dcon_req.append(module_id).append(to_milli_a(output_value));
	if (with_checksum) {
		dcon_req.append(int_to_hex_string(dcon_checksum(dcon_req)));
	}
	dcon_req.append("\r");

	int amount = write(com_port_fd, dcon_req.c_str(), dcon_req.size());

    if (amount < 0 || amount != dcon_req.size()){
        message_t () << "Error! Expected to send [" << dcon_req.size() << "] bytes, actually send [" << amount << "] bytes";
    } else {
        message_t () << "Message [" << dcon_req << "] was sent to module.";
    }

	return amount;
}


void get_data_from_socket(){
    struct sockaddr_in sock_addr;
    int socket_fd = create_socket(&sock_addr);
    std::vector<char> vec = std::vector<char>(sizeof(msg_t));
    msg_t *msg = (msg_t*) &vec[0];

    if(!init_serial_port(PORT_NAME)){
        message_t () << "Unable to set serial port connection!";
        return;
    }
    if (socket_fd < 0) {
        message_t () << "Unable to set socket connection!";
        send_to_module(0, WITH_CHKSUM);
        return;
    }

    values[PCKG_ID1].canal_id = 1;
    values[PCKG_ID2].canal_id = 2;
    values[PCKG_ID3].canal_id = 3;

    type_t packet;
    int recieve_bytes_amount;
    while(can_work){
        int len = sizeof(sock_addr);
        recieve_bytes_amount = recvfrom(socket_fd, &vec[0], vec.size(), MSG_WAITALL, (struct sockaddr*) &sock_addr, (socklen_t*) &len);

        if (recieve_bytes_amount >= sizeof(msg_t)){
            packet.msg = *msg;
            packet.receive_time = std::chrono::duration_cast<std::chrono::seconds> (std::chrono::system_clock::now().time_since_epoch());

            if (PCKG_ID1 <= msg->packet_id && msg->packet_id <= PCKG_ID3) {
                const std::lock_guard<std::mutex> lock(_mutex);

                values[msg->packet_id] = packet;
            }

        } else if(errno == EWOULDBLOCK || errno == EAGAIN){
            send_to_module(0, WITH_CHKSUM);
            message_t () << "Socket timeout!";
        }
    }

    close(socket_fd);
}

bool init_serial_port(const char* port_name) {
	com_port_fd = open(port_name, O_RDWR | O_NOCTTY);
	if (com_port_fd == -1) {
        message_t () << "Unable to open serial port";
		return false;
	}

	tcgetattr(com_port_fd, &old_settings);	

	struct termios new_port_settings;

	new_port_settings = old_settings;
	cfsetispeed(&new_port_settings,B9600);
	cfsetospeed(&new_port_settings,B9600);

	new_port_settings.c_cflag &= ~PARENB;
	new_port_settings.c_cflag &= ~CSTOPB;
	new_port_settings.c_cflag &= ~CSIZE;
	new_port_settings.c_cflag |=  CS8;
	
	new_port_settings.c_cflag &= ~CRTSCTS;
	new_port_settings.c_cflag |= CREAD | CLOCAL;
	
	
	new_port_settings.c_iflag &= ~(IXON | IXOFF | IXANY);
	new_port_settings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	new_port_settings.c_oflag &= ~OPOST;
	
	new_port_settings.c_cc[VMIN] = 0;
	new_port_settings.c_cc[VTIME] = 20; 

	if((tcsetattr(com_port_fd,TCSANOW,&new_port_settings)) != 0) {
        message_t () << "Unable to set com port attributes";
		close_com();
		return false;
	}

	return true;
}


int create_socket(struct sockaddr_in* sock_addr){
    int socket_fd;

    struct timeval timeout;          
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(socket_fd == -1) {
        message_t () << "Unable to create socket.";
        return socket_fd;
    }
    
    memset(sock_addr, 0, sizeof(sock_addr));
    sock_addr->sin_family = AF_INET;
    sock_addr->sin_port = htons(PORT);
    sock_addr->sin_addr.s_addr = inet_addr(SERVER);

    if (setsockopt (socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) < 0)
        message_t () << "Unable to set socket timeouts";

        if (bind(socket_fd, (const struct sockaddr *)sock_addr, sizeof(*sock_addr)) < 0 ){
            message_t () << "Unable to bind socket";
            perror("bind");
        }
    return socket_fd;
}


int get_deviation_index  (std::vector<float> &vec, float average) {
    const float max_deviation_ub = average * 1.15;
    const float max_deviation_lb = average * 0.85;


    int dev_idx = -1;
    float max_deviation = 0;
    for (int idx = 0; idx < vec.size(); ++idx) {
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

float get_average (std::vector<float> &vec, int deviation_index = -1){
    float sum = 0;
    int amount = 0;
    for (int idx = 0; idx < vec.size(); ++idx) {
        if (idx != deviation_index){
            ++amount;
            sum += vec[idx];
        }
    }

    return !amount ? 0 : sum / amount;
}


void data_processing(){
    float sum;
    int amount = 0;

    while(can_work){

        std::this_thread::sleep_for(TIMEOUT);

        std::chrono::seconds start_time = std::chrono::duration_cast<std::chrono::seconds> (std::chrono::system_clock::now().time_since_epoch());

        const std::lock_guard<std::mutex> lock(_mutex);

        sum = 0;
        amount = 0;

        std::vector<float> vec(3);
        for (auto pair : values){
            const int valid_state = 0;

            std::chrono::seconds time_differrence = start_time - pair.second.receive_time;
            if (time_differrence  < TIMEOUT){

                if (pair.second.msg.element[0].state == valid_state){
                    float value = pair.second.msg.element[0].value;

                    message_t () << "pair.first = " << pair.first;
                    vec[pair.first - 1] = value;
                    ++amount;
                } 
                else {
                    message_t () << '[' << pair.second.msg.packet_id << ']' << " canal invalid state [" << pair.second.msg.element[0].state << ']';
                }
            } else {
                message_t () << '[' << pair.second.msg.packet_id << ']' << " canal timeout [" << time_differrence.count() << ']';
            }
        }

        if (amount > 0){
            float average = get_average (vec);

            int current_deviation_index = get_deviation_index (vec, average);
            
            average = get_average (vec, current_deviation_index);
            
            send_to_module(average);
        } else {
            send_to_module(0.0000f);
            message_t () << "Invalid data!\n" << "Recieved [" << amount << "] messeges!";
        }
    }

    message_t(std::cout) << "The work is over";
}


// std::string to_milli_a(float value) {
// 	 if ((int) value == 0) {
// 	 	return "00.000";
// 	 }
         
// 	return "0" + std::to_string(value * 0.05).substr(0, 5);
// }

// std::string int_to_hex_string(int sum) {
// 	std::stringstream sstream;
// 	sstream << std::uppercase << std::hex << sum;
// 	return sstream.str();
// }

// int dcon_checksum(std::string& str) {
// 	int sum = 0;
// 	for (char ch : str) {
// 		sum += ch;
// 	}

// 	return sum & 0xFF;
// }

void close_com()
{
    tcsetattr(com_port_fd,TCSANOW,&old_settings);
    close(com_port_fd);
    com_port_fd = -1; 
}
