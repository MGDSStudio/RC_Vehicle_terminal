//
// Created by Alexander on 10.04.2026.
//

#ifndef CMAKESFMLPROJECT_GAMEPADDATASTRUCT_H
#define CMAKESFMLPROJECT_GAMEPADDATASTRUCT_H


#include <filesystem>
#include <string>
#include <unordered_map>
#include "../Constants.h"
#include <filesystem>
#include <nlohmann/json.hpp>
#include "InputKeys.h"
#include "GamepadInputNames.h"
#include <SDL3/SDL.h>

class GamepadDataStruct {

public:
    GamepadDataStruct();

    std::string getNameForButton(unsigned int button_code) const {
        if (button_code == buzzerButton) return BUZZER_DIGITAL;
        else if (button_code == gripperPressButton) return GRIPPER_PRESS;
        else if (button_code == gripperReleaseButton) return GRIPPER_RELEASE;
        else if (button_code == gripperUpButton) return GRIPPER_UP;
        else if (button_code == gripperDownButton) return GRIPPER_DOWN;
        else if (button_code == switch_off) return SWITCH_OFF;
        else if (button_code == upDigital) return MOVE_FORWARD_DIGITAL;
        else if (button_code == downDigital) return MOVE_BACKWARD_DIGITAL;
        else if (button_code == leftDigital) return ROTATE_CCW_DIGITAL;
        else if (button_code == rightDigital) return ROTATE_CW_DIGITAL;
        else {
            return NO_DATA;
        }
    }

    std::string getNameForAxis(SDL_GamepadAxis axis) {
        if (axis == xAxis) return ROTATION_ANALOG;
        else if (axis == yAxis) return MOVEMENT_ANALOG;
        else if (axis == buzzerAxis) return BUZZER_ANALOG;
        else return NO_DATA;
    }

private:
    const std::filesystem::path PATH = Constants::PATH_TO_DATA / "gamepad.json";
    std::unordered_map <std::string, int> buttonsMap;
    std::unordered_map <std::string, int> axesMap;

    void readButtonsData(nlohmann::json::const_reference json);

    void init();
        int buzzerButton = SDL_GAMEPAD_BUTTON_SOUTH;
        int gripperPressButton = -1;
        int gripperReleaseButton = -1;
        int gripperUpButton = -1;
        int gripperDownButton = -1;
        int switch_off = SDL_GAMEPAD_BUTTON_START;
        SDL_GamepadAxis xAxis = SDL_GAMEPAD_AXIS_LEFTX;
        SDL_GamepadAxis yAxis = SDL_GAMEPAD_AXIS_LEFTY;
        int leftDigital = SDL_GAMEPAD_BUTTON_DPAD_LEFT;
        int rightDigital = SDL_GAMEPAD_BUTTON_DPAD_RIGHT;
        int upDigital = SDL_GAMEPAD_BUTTON_DPAD_UP;
        int downDigital = SDL_GAMEPAD_BUTTON_DPAD_DOWN;
        SDL_GamepadAxis buzzerAxis = SDL_GAMEPAD_AXIS_RIGHT_TRIGGER;
};


#endif //CMAKESFMLPROJECT_GAMEPADDATASTRUCT_H
