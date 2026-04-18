//
// Created by gorod on 16.04.2026.
//

#include "ReleasePinHardware.h"

#include "../libs/GeometrieLibrary.h"

/*
ReleasePinHardware::ReleasePinHardware(int pinNumber)
{
    }

 */
void ReleasePinHardware::setValue(float value)
{
    #ifdef IS_RPI
        float mapped = mapForPwm(value);
        gpioPWM(pinNumber, mapped);
        log("PWM " + std::to_string(mapped)+ " was set for raw value: " + std::to_string(value));
    #endif
}

void ReleasePinHardware::enable(bool flag)
{
    #ifdef IS_RPI
        if (flag){
            gpioWrite(pinNumber, ENABLE_PIN);
            log("high level was set");
        }
        else {
            gpioWrite(pinNumber, DISABLE_PIN);
            log("low level was set");
        }
    #endif
}

void ReleasePinHardware::complete()
{
    #ifdef IS_RPI
        gpioWrite(pinNumber, DISABLE_PIN);
        log("completed. Pin was disabled");
    #endif
}

int ReleasePinHardware::mapForPwm(float fromNullToOne){
    //fromNullToOne = 1-fromNullToOne;
    //fromNullToOne = 1-fromNullToOne;
    float mapped = GeometrieLibrary::map(fromNullToOne, 0, 1,  ENABLED_PWM_VALUE, DISABLED_PWM_VALUE);
    mapped = DISABLED_PWM_VALUE-mapped;
    //float mapped = ostart + (ostop - ostart) * ((fromMinusOneUpToOne - istart) / (istop - istart));
    return (int)ENABLED_PWM_VALUE-mapped;
}
