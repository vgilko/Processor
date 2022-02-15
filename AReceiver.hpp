#pragma once

#include <vector>

class AReceiver {
public:
    virtual ~AReceiver () = default;

    virtual std::vector <char> receive () = 0;
};