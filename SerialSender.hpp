#pragma once

#include "ASender.hpp"

#include <string>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

class SerialSender : public ASender <std::string> {
public:
    SerialSender (std::string file_name, speed_t baud_rate);
    virtual ~SerialSender ();
  
private:
    std::mutex value_control;
    
    std::string value;
    
    int port_fd;
    std::string filename;

    struct termios old_settings;

    int send_unsync ();
    void set_value_unsync (std::string);


    void init_serial_port (std::string file_name, speed_t baud_rate);
    void set_serial_port_params (speed_t baud_rate);
};