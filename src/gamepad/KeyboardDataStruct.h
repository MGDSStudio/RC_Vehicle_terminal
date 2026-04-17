//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_KEYBOARDDATASTRUCT_H
#define RC_VEHICLE_TERMINAL_KEYBOARDDATASTRUCT_H
#include "SDL3/SDL_keycode.h"
#include "../LocalCommandPrefix.h"

class KeyboardDataStruct
{
public:
    [[nodiscard]] int getUp() const
    {
        return up;
    }

    [[nodiscard]] int getDown() const
    {
        return down;
    }

    [[nodiscard]] int getLeft() const
    {
        return left;
    }

    [[nodiscard]] int getRight() const
    {
        return right;
    }

    LocalCommandPrefix getPrefixForEvent(int key)
    {
        if (key == up) return LocalCommandPrefix::PREFIX_MOVEMENT_FORWARD;
        else if (key == down) return LocalCommandPrefix::PREFIX_MOVEMENT_FORWARD;
        else if (key == left) return LocalCommandPrefix::PREFIX_ROTATION_CCW;
        else if (key == right) return LocalCommandPrefix::PREFIX_ROTATION_CW;
        else if (key == switchOff) return LocalCommandPrefix::PREFIX_SWITCH_OFF;
        else
        {
            return LocalCommandPrefix::NO_DATA;
        }
    }

private:
    int up = SDLK_UP;
    int down = SDLK_DOWN;
    int left = SDLK_LEFT;
    int right = SDLK_RIGHT;
    int switchOff = SDLK_BACKSPACE;
};


#endif //RC_VEHICLE_TERMINAL_KEYBOARDDATASTRUCT_H