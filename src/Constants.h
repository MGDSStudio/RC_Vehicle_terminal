//
// Created by gorod on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_CONSTANTS_H
#define CMAKESFMLPROJECT_CONSTANTS_H

#include <string>
#include <filesystem>

class Constants {
public:
    static constexpr bool EVENT_PICKED_UP = true;
    static constexpr bool EVENT_CAN_NOT_ENCRYPTED = !EVENT_PICKED_UP;
    static constexpr float MAX_ANALOG_VALUE = 1;
    static constexpr float MIN_ANALOG_VALUE = -1;
    inline static const std::filesystem::path PATH_TO_DATA = "data";

    static constexpr float MIN_GAMEPAD_AXIS_VALUE = -32768;
    static constexpr float MAX_GAMEPAD_AXIS_VALUE = 32767;
    static constexpr float NEUTRAL_GAMEPAD_AXIS_VALUE = 0;
    static constexpr float NEUTRAL_ANALOG_VALUE = NEUTRAL_GAMEPAD_AXIS_VALUE;

    static constexpr float MIN_EFFECTIVE_PWM_VALUE_FOR_MAX_VALUE = 0;
    static constexpr float MAX_EFFECTIVE_PWM_VALUE_FOR_MIN_VALUE = 190;
    static constexpr float MIN_EFFECTIVE_ANALOG_VALUE = 0.08;
};


#endif //CMAKESFMLPROJECT_CONSTANTS_H