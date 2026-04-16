//
// Created by Alexander on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_SOFTWAREPIN_H
#define CMAKESFMLPROJECT_SOFTWAREPIN_H

#include "Pin.h"

class SoftwarePin : public Pin{

    public:    

    virtual ~SoftwarePin() override;

    SoftwarePin(int pinNumber);

    void setValue(float value) override;
    void enable(bool flag) override;
    void complete() override;

private:
    const std::string DEBUG_TEXT_PREFIX = "SOFTWARE_PIN ";
    const bool debug = false;
    inline static bool gpioInitialised;

};


#endif //CMAKESFMLPROJECT_SOFTWAREPIN_H
