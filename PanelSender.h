#pragma once

#include "ASender.hpp"
#include <modbus.h>

#include <vector>
#include <string>

#include <cstdint>

class PanelSender : public ASender<float> {
public:
    PanelSender(std::string port_name,
                int baud_rate = 115200, 
                char parity = 'N', 
                int bits_amount = 8, 
                int stop_bit = 1,
                bool with_debug = false);
    virtual ~PanelSender();


private:
    modbus_t* ctx;
    
    std::vector<uint16_t> message_to_send;
    

    
    int send_unsync ();
    void set_value_unsync (float value);
    
    std::vector<uint16_t> float_to_int_arr(float value);
    
    void set_modbus_connection (std::string port_name,
                                int baud_rate, 
                                char parity, 
                                int bits_amount, 
                                int stop_bit,
                                bool with_debug);
};