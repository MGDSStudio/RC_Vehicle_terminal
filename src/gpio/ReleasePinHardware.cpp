//
// Created by gorod on 16.04.2026.
//

#include "ReleasePinHardware.h"

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
    #endif
}

void ReleasePinHardware::enable(bool flag)
{
    #ifdef IS_RPI
        if (flag){
            gpioWrite(pinNumber, ENABLE_PIN);
            //gpioWrite(17, ENABLE_PIN);
            //gpioWrite(5, ENABLE_PIN);
            //gpioWrite(27, ENABLE_PIN);
            //gpioWrite(20, ENABLE_PIN);

            //gpioPWM(pinNumber, ENABLED_PWM_VALUE);
            log("high level was set");
        }
        else {
            gpioWrite(pinNumber, DISABLE_PIN);

            //gpioWrite(17, DISABLE_PIN);
            //gpioWrite(5, DISABLE_PIN);
            //gpioWrite(27, DISABLE_PIN);
            //gpioWrite(20, DISABLE_PIN);
            //gpioPWM(pinNumber, DISABLED_PWM_VALUE);
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

int ReleasePinHardware::mapForPwm(float fromMinusOneUpToOne){
    float ostart = -1;
    float ostop = 1;
    float istart = ENABLED_PWM_VALUE;
    float istop = DISABLED_PWM_VALUE;
    float mapped = ostart + (ostop - ostart) * ((fromMinusOneUpToOne - istart) / (istop - istart));
    return (int)mapped;
}
