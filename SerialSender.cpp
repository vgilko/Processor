#include "SerialSender.hpp"

#include <stdexcept>

SerialSender::SerialSender (std::string file_name, speed_t baud_rate) {
    if (!(baud_rate >= B0 && baud_rate <= B38400 || 
        baud_rate >= B57600 && baud_rate <= B4000000)) {

        throw std::invalid_argument("Invalid baud_rate value. You must use termios constants.");
    }

    if (file_name.empty()) {
        throw std::invalid_argument("Invalid file_name.");
    }

    init_serial_port (file_name, baud_rate);
}


SerialSender::~SerialSender () {
    tcsetattr (port_fd, TCSANOW, &old_settings);

    close (port_fd);
}


int SerialSender::send_unsync () {
    return write (port_fd, value.c_str (), value.size ());
}

void SerialSender::set_value_unsync (std::string value) {
    this->value = value;
}


void SerialSender::init_serial_port(std::string file_name, speed_t baud_rate) {
	port_fd = open(file_name.c_str(), O_RDWR | O_NOCTTY);
	if (port_fd == -1) {
        throw std::runtime_error("Unable to open serial port.");
	}

    set_serial_port_params (baud_rate);

}

void SerialSender::set_serial_port_params (speed_t baud_rate) {
    /** 
     *  Set serial port attributes. Baud rate will be set to baude_rate parameter;
     *  Other settings will be set to 8n1 mode.
    */

	tcgetattr(port_fd, &old_settings);	

	struct termios new_port_settings;

	new_port_settings = old_settings;
	cfsetispeed(&new_port_settings, baud_rate);
	cfsetospeed(&new_port_settings, baud_rate);

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

	if (tcsetattr (port_fd,TCSANOW,&new_port_settings) != 0) {
        throw std::runtime_error("Unable to set com port attributes.");
	}
}