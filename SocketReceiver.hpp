#pragma once

#include "AReceiver.hpp"

#include <string>
#include <vector>

#include <unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

class SocketReceiver : public AReceiver {
public:
    SocketReceiver (std::string address, 
                    uint16_t port, 
                    uint16_t timeout, 
                    uint16_t bytes_amount_for_receive);
    virtual ~SocketReceiver ();

    std::vector<char> receive ();

private:
    int socket_fd;
    struct sockaddr_in socket_info;
    socklen_t socket_length;

    std::vector <char> data;

    unsigned short bytes_amount_for_receive;

    void set_socket_connection (std::string address, uint16_t port, uint16_t timeout);
};