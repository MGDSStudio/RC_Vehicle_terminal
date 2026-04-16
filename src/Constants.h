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
};


#endif //CMAKESFMLPROJECT_CONSTANTS_H