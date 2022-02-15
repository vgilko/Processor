#include "SocketReceiver.hpp"

#include "message_t.hpp"

#include <errno.h>
#include <string.h>

#include <stdexcept>


SocketReceiver::SocketReceiver (std::string address, 
                                uint16_t port, 
                                uint16_t timeout, 
                                uint16_t bytes_amount_for_receive) 
{
    if (bytes_amount_for_receive <= 0) {
        throw std::invalid_argument("Invalid value of bytes_amount_for_receive argument.");
    }

    if (port <= 0) {
        throw std::invalid_argument("Invalid value of port argument.");
    }

    if (timeout <= 0) {
        throw std::invalid_argument("Invalid value of timeout argument.");
    }
    
    data = std::vector<char> (bytes_amount_for_receive);

    set_socket_connection (address, port, timeout);
}


SocketReceiver::~SocketReceiver ()
{
    close (socket_fd);
}


void SocketReceiver::set_socket_connection (std::string address, 
                                  uint16_t port, 
                                  uint16_t timeout) 
{
    struct timeval sock_timeout;          
    sock_timeout.tv_sec = timeout;
    sock_timeout.tv_usec = 0;

    socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(socket_fd == -1) {
        throw std::runtime_error("Unable to create socket.");        
    }
    
    memset(&socket_info, 0, sizeof (socket_info));
    socket_info.sin_family = AF_INET;
    socket_info.sin_port = htons (port);
    socket_info.sin_addr.s_addr = inet_addr (address.c_str ());

    if (setsockopt (socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&sock_timeout, sizeof(sock_timeout)) < 0)
        message_t () << "Unable to set socket timeouts";

    if (bind (socket_fd, (const struct sockaddr *) &socket_info, sizeof (socket_info)) < 0 ){
        throw std::runtime_error (std::string ("Unable to bind socket ") + strerror (errno));
    }

    socket_length = (socklen_t) sizeof (socket_info);
}


std::vector<char> SocketReceiver::receive ()
{
    recvfrom(socket_fd, &data[0], data.size(), MSG_WAITALL, (struct sockaddr*) &socket_info, &socket_length);
    return data;
}