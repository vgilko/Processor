#pragma once

#include "ASender.hpp"
#include "SerialSender.hpp"

#include <string>

#include <mutex>

class DconSender : public ASender <float> 
{
public:
    DconSender (std::string port_name, 
                speed_t baud_rate, 
                int module_id, 
                bool with_check_sum = false);
    virtual ~DconSender () = default;
    
    void set_value_unsync (float value);
    int send_unsync ();

private:
    std::string module_id;

    bool with_checksum;


    std::mutex value_control;

    SerialSender sender;


    std::string convert_to_analog ();

    std::string construct_message ();
    std::string int_to_hex_string (int);
    int dcon_checksum (std::string& str);
};