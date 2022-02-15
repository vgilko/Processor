/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PanelSender.cpp
 * Author: viktor
 * 
 * Created on 14 January 2022, 16:42
 */

#include "PanelSender.h"

#include "message_t.hpp"

#include <stdexcept>

#include <iostream>


PanelSender::PanelSender(std::string port_name,
                        int baud_rate, 
                        char parity, 
                        int bits_amount, 
                        int stop_bit,
                        bool with_debug) 
{
    set_modbus_connection (port_name, baud_rate, parity, bits_amount, stop_bit, with_debug);
}


PanelSender::~PanelSender() {
    
}


void PanelSender::set_value_unsync (float new_value)
{
    value = new_value;
    
    message_to_send = float_to_int_arr (value);
}



int PanelSender::send_unsync ()
{   
    int size = message_to_send.size() + 1;
    int amount = modbus_write_registers(ctx, 3000, size, &message_to_send[0]);
    
    if (amount != size){
        message_t () << "Error: too little data was sent\nExpectd to sent [" << size << "], actually [" << amount << "] symbols";
        message_t () << "Errno: [" << errno << "] => " << modbus_strerror(errno);
//        modbus_free(ctx);
    } else {
        message_t () << "Value [" << value << "] was sent to panel.";
    }
    
    return amount;
}


std::vector<uint16_t> PanelSender::float_to_int_arr(float value)
{
    std::vector<uint16_t> message_to_send;
    uint16_t val;
    const int letters_capacity = 8;

    std::ostringstream os;
    if (value < 1){
        os.precision(2);
        os.setf(std::ios_base::scientific | std::ios_base::uppercase);
    } else {
        os.precision(1);
        os.setf(std::ios_base::fixed);
    }
    os << value;
    std::string fls = os.str();

    size_t exp_position = fls.find('E');
    if (exp_position != std::string::npos && fls[fls.size() - 2] == '0'){
        fls.replace(fls.size() - 2, 1, "");
    }

    int end_position = 0;
    if (fls.size() < letters_capacity){
        end_position = (letters_capacity - fls.size())/2;
        for (int i = 0; i < end_position; ++i){
            message_to_send.push_back(0x3000); //unicode ' '
        }
    }

    for(size_t i = 0; i < fls.size(); ++i){
        val = 0xFF10 + (int) fls[i] - 48;
        message_to_send.push_back(val);
    }

    if (fls.size() < letters_capacity){
        message_to_send.push_back(0xFF05); //unicode '%'
    }

    return message_to_send;
}


void PanelSender::set_modbus_connection (std::string port_name,
                        int baud_rate = 115200, 
                        char parity = 'N', 
                        int bits_amount = 8, 
                        int stop_bit = 1,
                        bool with_debug = false)
{
    ctx = modbus_new_rtu (port_name.c_str (), baud_rate, parity, bits_amount, stop_bit);
    
    if (ctx == nullptr)
    {
        throw std::invalid_argument ("Invalid argument. Check the value before passed it.");
    }

    if(modbus_set_slave(ctx, 1 ) == -1){
        modbus_close(ctx);
        throw std::runtime_error ("Unable to set slave. Errno: ["  + std::to_string(errno) + "] => " + modbus_strerror(errno));

    }

    if (modbus_connect(ctx) == -1){

        modbus_close(ctx);
        throw std::runtime_error ("Unable to connect. Errno: ["  + std::to_string(errno) + "] => " + modbus_strerror(errno));
    }

    modbus_set_debug(ctx, with_debug);

    uint32_t tv_sec, tv_usec;
    modbus_get_response_timeout(ctx, &tv_sec, &tv_usec); 
    tv_sec = 4;
    tv_usec = 0;
    modbus_set_response_timeout(ctx, tv_sec,tv_usec); 
    
    message_t (std::cout) << "Modbus connection was set up.";
}
