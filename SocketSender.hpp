#pragma once

#include "ASender.hpp"

#include <string>
#include <cstdint>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

enum class proto_t{TCP, UDP};

template <class value_t>
class SocketSender : public ASender <value_t>
{
public:

    SocketSender(std::string address, uint16_t port, proto_t protocol);
	~SocketSender();
private:
    int socket_fd;
    struct sockaddr_in socket_info;

    
    int send_unsync ();
    void set_value_unsync (value_t new_value);

    
    void set_socket_connection (std::string address, uint16_t port, proto_t protocol);
};