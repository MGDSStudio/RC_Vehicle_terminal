//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_KEYBOARDCONTROLLER_H
#define RC_VEHICLE_TERMINAL_KEYBOARDCONTROLLER_H
#include "InputController.h"
#include "KeyboardDataStruct.h"
#include "../IUpdateable.h"
#include "../LocalCommandPrefix.h"


class KeyboardController : public IUpdateable, InputController
{
public:
    KeyboardController();
    ~KeyboardController() override;
    void update(float tpf) override;
    void complete() override;
    bool attachCommand(SDL_Event* event) override;

private:
    KeyboardDataStruct keyboard_data_struct;
    inline static bool debug = true;
};


#endif //RC_VEHICLE_TERMINAL_KEYBOARDCONTROLLER_H