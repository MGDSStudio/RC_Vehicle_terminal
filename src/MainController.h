//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_MAINCONTROLLER_H
#define RC_VEHICLE_TERMINAL_MAINCONTROLLER_H

#include "IUpdateable.h"
#include <SDL3/SDL.h>

#include "gamepad/GamepadController.h"
#include "gamepad/KeyboardController.h"
#include "BuzzerController.h"
#include "MovementController.h"

class MainController : public IUpdateable
{
public:
    MainController();
    ~MainController() override;
    void update(float tpf) override;
    void complete() override;
    void attachCompletionFlagData(bool* completeFlag)
    {
        this->completeFlagApplicationLevel = completeFlag;
    }

private:
    bool* completeFlagApplicationLevel = nullptr;
    bool completeFlagInputLevel = false;
    int frames = 0;
    GamepadController gamepadController;
    BuzzerController buzzerController;
    MovementController movementController;
    SDL_Event event;
    void close() const
    {
        *this->completeFlagApplicationLevel = true;
    }
};


#endif //RC_VEHICLE_TERMINAL_MAINCONTROLLER_H