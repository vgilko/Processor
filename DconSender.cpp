#include "DconSender.hpp"
#include "message_t.hpp"

#include <sstream>


DconSender::DconSender (std::string port_name, 
                        speed_t baud_rate, 
                        int module_id, 
                        bool with_check_sum)
    : sender(port_name, baud_rate)
{
    this->module_id = std::to_string(module_id);
    with_checksum = with_check_sum;

}


int DconSender::send_unsync () {

    std::string message = construct_message ();
    
    sender.set_value (message);
    size_t amount = sender.send();

    if (amount < 0 || amount != message.size()){
        message_t () << "Error! Expected to send [" << message.size() << "] bytes, actually send [" << amount << "] bytes";
    } else {
        message_t () << "Message [" << message << "] was sent to module.";
    }

    return amount;
}


void DconSender::set_value_unsync (float new_value) {
    value = new_value;
}


std::string DconSender::construct_message () {
    std::string message = "#";
	message.append (module_id).append (convert_to_analog());

	if (with_checksum) {
            message.append (int_to_hex_string (dcon_checksum (message)));
	}
    
	message.append("\r");
        
        return message;
}


std::string DconSender::convert_to_analog () {
    const std::unique_lock <std::mutex> lock (value_control);
    if ((int) value == 0) {
        return "00.000";
    }
        
    return "0" + std::to_string (value * 0.05).substr (0, 5);
}


std::string DconSender::int_to_hex_string (int value) {
    const std::unique_lock <std::mutex> lock (value_control);

	std::stringstream sstream;
	sstream << std::uppercase << std::hex << value;
	return sstream.str();
}



int DconSender::dcon_checksum(std::string& str) {
    int sum = 0;
    for (char ch : str) {
        sum += ch;
    }

    return sum & 0xFF;
}