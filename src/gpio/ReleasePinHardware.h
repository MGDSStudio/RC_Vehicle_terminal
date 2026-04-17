//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_RELEASEPINHARDWARE_H
#define RC_VEHICLE_TERMINAL_RELEASEPINHARDWARE_H
#include "ReleasePin.h"
#include "../Logger.h"

#ifdef IS_RPI
    #include <pigpio.h>
#endif

static bool gpioInitialised = false;

class ReleasePinHardware : public ReleasePin
{
public:
    ReleasePinHardware(int pinNumber) : ReleasePin(pinNumber, true, "HARDWARE_PIN"){
        if (!gpioInitialised) {
        #ifdef IS_RPI
            auto errorCode = gpioInitialise();
            if (errorCode < 0) {
                Logger::criticalError("GPIO can not be init. Error code: " + std::to_string(errorCode));
                /*
                PI_INIT_FAILED (-1) — общая ошибка (часто из-за sudo).
                PI_BAD_MALLOC_PRIVS (-132) — нет прав на выделение памяти (точно sudo).
                -70 (PI_CAN_OPEN_PIGPIOD) — интерфейс занят.
                */
            }
            gpioInitialised = true;
        #endif
        }

    }
    ~ReleasePinHardware() override = default;
    void setValue(float value) override;
    void enable(bool flag) override;
    void complete() override;

private:
    constexpr static int ENABLE_PIN = 0;
    constexpr static int DISABLE_PIN = 1;
    const std::string DEBUG_TEXT_PREFIX = "HARDWARE_PIN";
    const int ENABLED_PWM_VALUE = 0;
    const int DISABLED_PWM_VALUE = 255;
    int mapForPwm(float fromMinusOneUpToOne);
};


#endif //RC_VEHICLE_TERMINAL_RELEASEPINHARDWARE_H