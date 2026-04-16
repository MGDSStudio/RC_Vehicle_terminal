//
// Created by gorod on 16.04.2026.
//

#include "KeyboardController.h"

#include "../Constants.h"
#include "../LocalCommand.h"
#include "../LocalCommandsListenersObserverSingleton.h"
#include "../Logger.h"

KeyboardController::KeyboardController()
{
    if (debug)
    {
        Logger::debug("Keyboard controller created");
    }
}

KeyboardController::~KeyboardController()
{

}

void KeyboardController::update(float tpf)
{

}

void KeyboardController::complete()
{

}

bool KeyboardController::attachCommand(SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_DOWN)
    {
        auto prefix = keyboard_data_struct.getPrefixForEvent(event->key.key);
        if (prefix != LocalCommandPrefix::NO_DATA)
        {
            float float_value = 1;
            if (event->type == SDL_EVENT_KEY_DOWN)
            {
                float_value = Constants::MAX_GAMEPAD_AXIS_VALUE;
            }
            else
            {
                float_value = Constants::NEUTRAL_GAMEPAD_AXIS_VALUE;
            }
            LocalCommand local_command(prefix, float_value);
            LocalCommandsListenersObserverSingleton::getInstance().broadcast(local_command);
            if (debug)
            {
                Logger::custom("KEYBOARD: ", "created command for prefix: " + std::to_string(int(event->type)) + " and value: " + std::to_string(float_value));
            }
            return true;
        }
        else return false;
    }
    else return false;
}



