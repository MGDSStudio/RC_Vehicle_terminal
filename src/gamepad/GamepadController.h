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
    SDL_Gamepad* gamepad = nullptr;
    GamepadDataStruct gamepad_data_struct;
    inline static bool debug = true;
    inline static std::string DEBUG_PREFIX = "GAMEPAD: ";
    bool* completeFlagInputLevel = nullptr;

    LocalCommandPrefix getPrefixForButton(uint8_t buttonCode);

    static void log(std::string text)
    {
        if (debug)
        {
            Logger::custom(DEBUG_PREFIX, text);
        }
    }

};



#endif //RC_VEHICLE_TERMINAL_GAMEPADCONTROLLER_H