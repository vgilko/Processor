#pragma once

#include <sstream>
#include <iostream>

class message_t : public std::stringstream{
public:
    message_t(): stream(std::cerr){}

    message_t(std::ostream &s) : stream(s){}

    ~message_t(){
        stream << this->str() << std::endl;
    }

private:
    std::ostream& stream;
};
