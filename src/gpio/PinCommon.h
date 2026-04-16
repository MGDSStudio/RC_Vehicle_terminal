//
// Created by Alexander on 11.04.2026.
//

#ifndef CMAKESFMLPROJECT_PINCOMMON_H
#define CMAKESFMLPROJECT_PINCOMMON_H

#include <string>


#ifdef IS_RPI
    #include <pigpio.h>
    const bool is_raspberry_pi = IS_RPI;
#else
    const bool is_raspberry_pi = false;
#endif


class PinCommon {
public:
    PinCommon(const int number);
    ~PinCommon() = default;
    void setValue(float value);
    void enable(bool flag);
    void complete();

protected:
    int hardwareNumber;
    std::string name;
    std::string numberAsString;
    const std::string DEBUG_TEXT_PREFIX_COMMON = "PIN ";
    std::string debugTextPrefix;
    const bool debug = false;
    const int ENABLED_PWM_VALUE = 0;
    const int DISABLED_PWM_VALUE = 255;

    int mapForPwm(float fromMinusOneUpToOne);
};

#endif //CMAKESFMLPROJECT_PINCOMMON_H
