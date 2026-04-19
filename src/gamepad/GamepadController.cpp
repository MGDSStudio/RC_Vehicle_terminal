//
// Created by gorod on 16.04.2026.
//

#include "GamepadController.h"

#include "../libs/GeometrieLibrary.h"
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
            updateButtonPressed(event, &local_command);
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            updateButtonReleased(event, &local_command);
            break;
        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
            updateAxisMoved(event, &local_command);
            break;
    }
    if (local_command.getPrefix() != LocalCommandPrefix::NO_DATA) LocalCommandsListenersObserverSingleton::getInstance().broadcast(local_command);
}

void GamepadController::updateButtonPressed(SDL_Event* event, LocalCommand* local_command)
{
    const auto localPrefix = getPrefixForButton(event->gbutton.button);
    local_command->setPrefix(localPrefix);
    local_command->setFloatValue(Constants::MAX_ANALOG_VALUE);  //Not important
    local_command->setBoolValue(true);
}

void GamepadController::updateButtonReleased(SDL_Event* event, LocalCommand* local_command)
{
    const auto localPrefix = getPrefixForButton(event->gbutton.button);
    local_command->setPrefix(localPrefix);
    local_command->setFloatValue(Constants::NEUTRAL_ANALOG_VALUE);  //Not important
    local_command->setBoolValue(false);
}


void GamepadController::updateAxisMoved(SDL_Event* event, LocalCommand* local_command)
{
    SDL_GamepadAxis axisType = static_cast<SDL_GamepadAxis>(event->gaxis.axis);
    auto axis_value = event->gaxis.value;   //-32000 + 32000
    const LocalCommandPrefix localPrefix = getPrefixForAxis(axisType, axis_value);
    float mappedAxisValue;
    local_command->setPrefix(localPrefix);
    if (axis_value < AXIS_DEAD_ZONE_MIN || axis_value > AXIS_DEAD_ZONE_MAX) {
        mappedAxisValue = map(localPrefix, axis_value);
    }
    else
    {
        mappedAxisValue = 0;
    }
    local_command->setFloatValue(mappedAxisValue);
}

LocalCommandPrefix GamepadController::getPrefixForAxis(const SDL_GamepadAxis& gaxis, Sint16 value)
{
    const std::string name = gamepad_data_struct.getNameForAxis(gaxis);
    auto local_command_prefix = LocalCommandPrefix::NO_DATA;
    if (name != NO_DATA)
    {
        if (name == MOVEMENT_ANALOG)
        {
            local_command_prefix = LocalCommandPrefix::PREFIX_MOVEMENT_ANALOG;
        }
        else if (name == ROTATION_ANALOG)
        {
            local_command_prefix = LocalCommandPrefix::PREFIX_ROTATION_ANALOG;
        }
        else if (name == ROTATION_CW_ANALOG) local_command_prefix = LocalCommandPrefix::PREFIX_ROTATION_CW_ANALOG;
        else if (name == ROTATION_CCW_ANALOG) local_command_prefix = LocalCommandPrefix::PREFIX_ROTATION_CCW_ANALOG;
        else if (name == BUZZER_ANALOG)
        {
            local_command_prefix = LocalCommandPrefix::PREFIX_NOISE_ANALOG;
        }
        else
        {
            log("Not known axis " + name);
        }
    }
    return local_command_prefix;
}

LocalCommandPrefix GamepadController::getPrefixForButton(uint8_t buttonCode)
{
    const std::string name = gamepad_data_struct.getNameForButton(buttonCode);
    auto local_command_prefix = LocalCommandPrefix::NO_DATA;
    if (name != NO_DATA) {
        if (name == BUZZER_DIGITAL) {
            local_command_prefix = LocalCommandPrefix::PREFIX_NOISE_DIGITAL;
        }
        else if (name == SWITCH_OFF) {
            local_command_prefix = LocalCommandPrefix::PREFIX_SWITCH_OFF;
            //if (this->completeFlagInputLevel != nullptr) {
                *this->completeFlagInputLevel = true;
            //}
        }
        else if (name == PAUSE) {
            local_command_prefix = LocalCommandPrefix::PREFIX_PAUSE;
        }
        else if (name == MOVE_FORWARD_DIGITAL)
        {
            local_command_prefix = LocalCommandPrefix::PREFIX_MOVEMENT_FORWARD;
        }
        else if (name == MOVE_BACKWARD_DIGITAL)
        {
            local_command_prefix = LocalCommandPrefix::PREFIX_MOVEMENT_BACKWARD;
        }
        else if (name == ROTATE_CCW_DIGITAL)
        {
            local_command_prefix = LocalCommandPrefix::PREFIX_ROTATION_CCW_DIGITAL;
        }
        else if (name == ROTATE_CW_DIGITAL)
        {
            local_command_prefix = LocalCommandPrefix::PREFIX_ROTATION_CW_DIGITAL;
        }
    }
    return local_command_prefix;
}

float GamepadController::getLowerBoundForPrefix(const LocalCommandPrefix prefix) {
    if (prefix == LocalCommandPrefix::PREFIX_ROTATION_CCW_ANALOG || prefix == LocalCommandPrefix::PREFIX_ROTATION_CW_ANALOG){
        return Constants::NEUTRAL_ANALOG_VALUE;
    }
    else return Constants::MIN_ANALOG_VALUE;
}

/*
LocalCommandPrefix GamepadController::getPrefixForAxis(const SDL_GamepadAxis& gaxis, Sint16 value)
{
    const std::string name = gamepad_data_struct.getNameForAxis(gaxis);
    auto local_command_prefix = LocalCommandPrefix::NO_DATA;
    if (name != NO_DATA)
    {
        if (name == MOVEMENT_ANALOG)
        {
            if (value>0) local_command_prefix = LocalCommandPrefix::MOVEMENT_FORWARD;
            else local_command_prefix = LocalCommandPrefix::MOVEMENT_BACKWARD;
        }
        else if (name == ROTATION_ANALOG)
        {
            if (value>0) local_command_prefix = LocalCommandPrefix::ROTATION_CW;
            else local_command_prefix = LocalCommandPrefix::ROTATION_CCW;
        }
        else if (name == BUZZER_ANALOG)
        {
            local_command_prefix = LocalCommandPrefix::NOISE_ANALOG;
        }
        else
        {
            log("Not known axis " + name);
        }
    }
    return local_command_prefix;
}

*/