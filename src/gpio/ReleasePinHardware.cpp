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
            gpioWrite(pinNumber, PI_HIGH);
            //gpioPWM(pinNumber, ENABLED_PWM_VALUE);
            log("high level set");
        }
        else {
            gpioWrite(pinNumber, PI_LOW);
            //gpioPWM(pinNumber, DISABLED_PWM_VALUE);
            log("low level set");
        }
    #endif
}

void ReleasePinHardware::complete()
{
    #ifdef IS_RPI
        gpioPWM(pinNumber, DISABLED_PWM_VALUE);
        log("completed. Pin PWM-value set to " + std::to_string(DISABLED_PWM_VALUE));
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
