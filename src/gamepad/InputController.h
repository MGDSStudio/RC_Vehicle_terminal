//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_INPUTCONTROLLER_H
#define RC_VEHICLE_TERMINAL_INPUTCONTROLLER_H
#include "SDL3/SDL_events.h"


class InputController
{
public:
    virtual bool attachCommand(SDL_Event* event) = 0;
};


#endif //RC_VEHICLE_TERMINAL_INPUTCONTROLLER_H