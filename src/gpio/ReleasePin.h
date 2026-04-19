//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_RELEASEPIN_H
#define RC_VEHICLE_TERMINAL_RELEASEPIN_H
#include <string>
#include "../Logger.h"

class ReleasePin
{

public:
    ReleasePin(int pinNumber, bool debug, std::string prefix){
        this->pinNumber = pinNumber;
        this->debug = debug;
        this->debugPrefixName = (prefix +  + " " + std::to_string(pinNumber) + ": ");
    }
    virtual ~ReleasePin() = default;
    virtual void setValue(float value) = 0;
    virtual void enable(bool flag) = 0;
    virtual void complete() = 0;
private:
    inline static int NOT_INIT_PIN_VAL = -1;

protected:
    bool debug = false;
    int pinNumber = NOT_INIT_PIN_VAL;
    std::string debugPrefixName = "PIN: ";

    void log(std::string text)
    {
        if (debug && pinNumber != NOT_INIT_PIN_VAL)
        {
            Logger::custom(debugPrefixName, text);
        }
    }
    /*void initDebug(bool debug, std::string text)
    {
        this->debug = debug;
        this->debugPrefixName = (text +  + ": ");
    }*/
};


#endif //RC_VEHICLE_TERMINAL_RELEASEPIN_H