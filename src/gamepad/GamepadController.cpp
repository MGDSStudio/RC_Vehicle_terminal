//
// Created by gorod on 16.04.2026.
//

#include "GamepadController.h"

#include "../LocalCommandsListenersObserverSingleton.h"

GamepadController::GamepadController() {
    log("Gamepad controller init");
}

GamepadController::~GamepadController() {
    complete();
}


void GamepadController::update(float tpf)
{
    //Logger::debug("Update");
}

void GamepadController::complete()
{
    if (gamepad != nullptr) {
        SDL_CloseGamepad(gamepad);
        gamepad = nullptr;
    }
}

bool GamepadController::attachCommand(SDL_Event* event)
{
    bool attached = true;
    if (isConnectionEvent(event))
    {
        applyConnectionEvent(event);
    }
    else if (isInputEvent(event))
    {
        applyInputEvent(event);
    }
    else attached = false;
    return attached;
}

bool GamepadController::isConnectionEvent(SDL_Event* event)
{
    return (event->type == SDL_EVENT_GAMEPAD_ADDED || event->type == SDL_EVENT_GAMEPAD_REMOVED);
}

bool GamepadController::isInputEvent(SDL_Event* event)
{
    //auto type = event->type;
    return (event->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN || event->type == SDL_EVENT_GAMEPAD_BUTTON_UP || event->type == SDL_EVENT_GAMEPAD_AXIS_MOTION);
}

void GamepadController::applyConnectionEvent(SDL_Event* event){
    switch (event->type)
    {
    case SDL_EVENT_GAMEPAD_ADDED:
        if (!gamepad) {
            gamepad = SDL_OpenGamepad(event->gdevice.which);
            std::string nameAsString = SDL_GetGamepadName(gamepad);
            log("Gamepad " + nameAsString + " added ");
        }
        break;
    case SDL_EVENT_GAMEPAD_REMOVED:
        if (gamepad && event->gdevice.which == SDL_GetGamepadID(gamepad)) {
            std::string nameAsString = SDL_GetGamepadName(gamepad);
            log("Gamepad  " + nameAsString + "removed ");
            SDL_CloseGamepad(gamepad);
            gamepad = nullptr;
        }
        break;
    }
}

void GamepadController::applyInputEvent(SDL_Event* event)
{
    LocalCommand local_command;
    switch (event->type)
    {
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        if (event->gbutton.button == SDL_GAMEPAD_BUTTON_SOUTH) { // 'A' on Xbox, 'Cross' on PS
            updateButtonPressed(event, &local_command);
        }
        break;
    case SDL_EVENT_GAMEPAD_BUTTON_UP:
        if (event->gbutton.button == SDL_GAMEPAD_BUTTON_SOUTH) { // 'A' on Xbox, 'Cross' on PS
            updateButtonReleased(event, &local_command);
        }
        break;
    case SDL_EVENT_GAMEPAD_AXIS_MOTION:
        updateAxisMoved(event, &local_command);
        break;
    }
    LocalCommandsListenersObserverSingleton::getInstance().broadcast(local_command);
}

void GamepadController::updateButtonPressed(SDL_Event* event, LocalCommand* local_command)
{
    const auto localPrefix = getPrefixForButton(event->gbutton.button);
    local_command->setPrefix(localPrefix);
    local_command->setFloatValue(Constants::MAX_GAMEPAD_AXIS_VALUE);
    local_command->setBoolValue(true);
}

void GamepadController::updateButtonReleased(SDL_Event* event, LocalCommand* local_command)
{
    const auto localPrefix = getPrefixForButton(event->gbutton.button);
    local_command->setPrefix(localPrefix);
    local_command->setFloatValue(Constants::NEUTRAL_GAMEPAD_AXIS_VALUE);
    local_command->setBoolValue(false);
}

void GamepadController::updateAxisMoved(SDL_Event* event, LocalCommand* local_command)
{
    constexpr int deadzone = 8000;
    if (SDL_abs(event->gaxis.value) > deadzone) {
        /*if (event.gaxis.axis == SDL_GAMEPAD_AXIS_LEFT_X) {
            std::cout << "Left Stick X: " << event.gaxis.value << std::endl;
        }
        if (event.gaxis.axis == SDL_GAMEPAD_AXIS_LEFT_Y) {
            std::cout << "Left Stick Y: " << event.gaxis.value << std::endl;
        }*/
    }
}

LocalCommandPrefix GamepadController::getPrefixForButton(uint8_t buttonCode)
{
    const std::string name = gamepad_data_struct.getNameForButton(buttonCode);
    auto local_command_prefix = LocalCommandPrefix::NO_DATA;
    if (name != NO_DATA) {
        if (name == BUZZER_DIGITAL) {
            local_command_prefix = LocalCommandPrefix::NOISE_DIGITAL;
        }
        else if (name == SWITCH_OFF) {
            local_command_prefix = LocalCommandPrefix::SWITCH_OFF;
            //if (this->completeFlagInputLevel != nullptr) {
                *this->completeFlagInputLevel = true;
            //}
        }
        else if (name == PAUSE) {
            local_command_prefix = LocalCommandPrefix::PAUSE;
        }
        else if (name == MOVE_FORWARD_DIGITAL)
        {
            local_command_prefix = LocalCommandPrefix::MOVEMENT_FORWARD;
        }
        else if (name == MOVE_BACKWARD_DIGITAL)
        {
            local_command_prefix = LocalCommandPrefix::MOVEMENT_BACKWARD;
        }
        else if (name == ROTATE_CCW_DIGITAL)
        {
            local_command_prefix = LocalCommandPrefix::ROTATION_CCW;
        }
        else if (name == ROTATE_CW_DIGITAL)
        {
            local_command_prefix = LocalCommandPrefix::ROTATION_CW;
        }
    }
    return local_command_prefix;
}