//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_GAMEPADCONTROLLER_H
#define RC_VEHICLE_TERMINAL_GAMEPADCONTROLLER_H
#include <iostream>
#include <ostream>
#include <string>

#include "GamepadDataStruct.h"
#include "InputController.h"
#include "../IUpdateable.h"
#include "../Logger.h"
#include "../LocalCommand.h"
#include "../GeometrieLibrary.h"

class GamepadController : public IUpdateable, InputController
{
public:
    GamepadController();

    ~GamepadController() override ;
    void update(float tpf) override;
    void complete() override;
    void updateButtonPressed(SDL_Event* event, LocalCommand* local_command);
    void updateButtonReleased(SDL_Event* event, LocalCommand* local_command);

    void updateAxisMoved(SDL_Event* event, LocalCommand* local_command);

    bool isConnectionEvent(SDL_Event* event);
    bool isInputEvent(SDL_Event* event);
    void applyConnectionEvent(SDL_Event* event);
    void applyInputEvent(SDL_Event* event);
    bool attachCommand(SDL_Event* event) override;
    void attachCompletionFlagData(bool* completeFlag)
    {
        this->completeFlagInputLevel = completeFlag;
    }

private:
    inline static Sint16 AXIS_DEAD_ZONE_MAX = 4000;
    inline static Sint16 AXIS_DEAD_ZONE_MIN = -4000;

    SDL_Gamepad* gamepad = nullptr;
    GamepadDataStruct gamepad_data_struct;
    inline static bool debug = true;
    inline static std::string DEBUG_PREFIX = "GAMEPAD: ";
    bool* completeFlagInputLevel = nullptr;

    LocalCommandPrefix getPrefixForAxis(const SDL_GamepadAxis& gaxis, Sint16 value);
    LocalCommandPrefix getPrefixForButton(uint8_t buttonCode);

    static void log(std::string text)
    {
        if (debug)
        {
            Logger::custom(DEBUG_PREFIX, text);
        }
    }

    static float map(LocalCommandPrefix local_command_prefix, float rawGamepadValue)
    {
        float min;
        if (local_command_prefix == LocalCommandPrefix::PREFIX_NOISE_ANALOG)
        {
            min = Constants::NEUTRAL_GAMEPAD_AXIS_VALUE;
        }
        else
        {
            min = Constants::MIN_ANALOG_VALUE;
        }
        return GeometrieLibrary::map(rawGamepadValue, Constants::MIN_GAMEPAD_AXIS_VALUE, Constants::MAX_GAMEPAD_AXIS_VALUE, min, Constants::MAX_ANALOG_VALUE);
    }

};



#endif //RC_VEHICLE_TERMINAL_GAMEPADCONTROLLER_H