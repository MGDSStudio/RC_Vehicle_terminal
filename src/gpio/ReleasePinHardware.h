//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_RELEASEPINHARDWARE_H
#define RC_VEHICLE_TERMINAL_RELEASEPINHARDWARE_H
#include "ReleasePin.h"
#ifdef IS_RPI
    #include <pigpio.h>
#endif


class ReleasePinHardware : public ReleasePin
{
public:
    ReleasePinHardware(int pinNumber) : ReleasePin(pinNumber, true, "HARDWARE_PIN "){
    }
    ~ReleasePinHardware() override = default;
    void setValue(float value) override;
    void enable(bool flag) override;
    void complete() override;

private:
    const std::string DEBUG_TEXT_PREFIX = "HARDWARE_PIN ";
    const int ENABLED_PWM_VALUE = 0;
    const int DISABLED_PWM_VALUE = 255;
    int mapForPwm(float fromMinusOneUpToOne);
};


#endif //RC_VEHICLE_TERMINAL_RELEASEPINHARDWARE_H