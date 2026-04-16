//
// Created by Alexander on 11.04.2026.
//

#include "PinCommon.h"

#include "../Logger.h"


PinCommon::PinCommon(const int number){
    this->hardwareNumber = number;
    this->numberAsString = std::to_string(number);
    this->debugTextPrefix = DEBUG_TEXT_PREFIX_COMMON+std::to_string(number);
    #ifdef IS_RPI
        gpioSetMode(hardwareNumber, PI_OUTPUT);
        Logger::debug("PIN " + numberAsString+ " set as output ");
    #endif
    //Logger::debug()
}

void PinCommon::setValue(const float value) {
    int mapped = mapForPwm(value);
    bool appliedForPi = false;
    #ifdef IS_RPI
        appliedForPi = true;
        gpioPWM(hardwareNumber, mapped);
        Logger::debug("GPIO value is " + std::to_string(mapped));
    #endif
    if (debug){
        const std::string text = " is set value: "+ std::to_string(value) + "; mapped: " + std::to_string(mapped) + " applied for PI: " + std::to_string(appliedForPi);
        Logger::custom(debugTextPrefix, text);
    }
}

void PinCommon::enable(const bool flag) {
    float appliedForPi = false;
    #ifdef IS_RPI
        appliedForPi = true;
        if (flag){
            gpioPWM(hardwareNumber, ENABLED_PWM_VALUE);
        }
        else {
            gpioPWM(hardwareNumber, DISABLED_PWM_VALUE);
        }
        Logger::debug("GPIO " + std::to_string(this->hardwareNumber) + "was has changed value");
    #endif

}

void PinCommon::complete(){
    #ifdef IS_RPI
        gpioPWM(hardwareNumber, DISABLED_PWM_VALUE);
    #endif
}

int PinCommon::mapForPwm(float fromMinusOneUpToOne){
    float ostart = -1;
    float ostop = 1;
    float istart = ENABLED_PWM_VALUE;
    float istop = DISABLED_PWM_VALUE;
    float mapped = ostart + (ostop - ostart) * ((fromMinusOneUpToOne - istart) / (istop - istart));
    return (int)mapped;
}
