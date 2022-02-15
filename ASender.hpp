#pragma once
#include <mutex>

template <class value_t>
class ASender {
public:
    virtual ~ASender () {}
    
    
    int send ()
    {
        const std::unique_lock <std::mutex> lock (value_control);

        return send_unsync ();
    }
    
    void set_value (value_t new_value) 
    {
        const std::unique_lock <std::mutex> lock (value_control);

        set_value_unsync (new_value);
    }

protected :
    virtual int send_unsync () = 0;
    virtual void set_value_unsync (value_t) = 0;

    value_t value;
    
private :
    std::mutex value_control;
        
};