//
// Created by Alexander on 09.04.2026.
//

#ifndef RC_VEHICLE_PIN_H
#define RC_VEHICLE_PIN_H

#include <string>
#include "../Logger.h"

class Pin {
public:
    Pin(int number){
        this->hardwareNumber = number;
        this->numberAsString = std::to_string(number);
        Logger::debug("Pin " + numberAsString + " initialised");
    }
    virtual ~Pin() = default;
    virtual void setValue(float value) = 0;
    virtual void enable(bool flag) = 0;
    virtual void complete() = 0;

protected:
    int hardwareNumber;
    std::string name;
    std::string numberAsString;
};


#endif //RC_VEHICLE_PIN_H
