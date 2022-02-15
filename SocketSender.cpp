/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.;
 */

/* 
 * File:   SocketSender.cpp
 * Author: viktor
 * 
 * Created on 20 January 2022, 16:44
 */

#include "SocketSender.hpp"


template <class value_t>
SocketSender<value_t>::SocketSender(std::string address, 
                                    uint16_t port, 
                                    proto_t protocol) 
{   
    set_socket_connection (address, port, protocol);
}

template <class value_t>
SocketSender<value_t>::~SocketSender ()
{
    close (socket_fd);
}


template <class value_t>
void SocketSender<value_t>::set_value_unsync (value_t new_value) 
{   
    this->value = new_value;
}

template <class value_t>
int SocketSender<value_t>::send_unsync ()
{
    return write (socket_fd, &this->value, sizeof (value_t));
}


template <class value_t>
void SocketSender<value_t>::set_socket_connection (std::string address, 
                                                uint16_t port, 
                                                proto_t protocol)
{
    if (protocol == proto_t::UDP) 
    {
        socket_fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    } 
    else if (protocol == proto_t::TCP) 
    {
        socket_fd = socket (AF_INET, SOCK_STREAM, 0);
    } else {
        throw std::invalid_argument ("Invalid protocol.");
    }
    
    if (socket_fd < 0)
    {
        throw std::runtime_error ("Unable to create socket.");
    }
    

    socket_info = {0};
    socket_info.sin_family = AF_INET;
    socket_info.sin_port = port;
    socket_info.sin_addr.s_addr = inet_addr (address.c_str ());
}
