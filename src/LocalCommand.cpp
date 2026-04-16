//
// Created by Alexander on 09.04.2026.
//

#include "LocalCommand.h"

#include "Constants.h"

int LocalCommand::counter = 0;

LocalCommand::LocalCommand(LocalCommandPrefix globalCommandPrefix, float param) {
    this->prefix = globalCommandPrefix;
    this->floatValue = param;
    setId();
}

LocalCommand::LocalCommand(LocalCommandPrefix globalCommandPrefix, bool enabled) {
    this->prefix = globalCommandPrefix;
    this->boolValue = enabled;
    if (enabled)
    {
        floatValue = Constants::MAX_GAMEPAD_AXIS_VALUE;
    }
    else floatValue = Constants::NEUTRAL_GAMEPAD_AXIS_VALUE;
    setId();
}

LocalCommand::LocalCommand() {
    setId();
}

void LocalCommand::setId(){
    this->id = counter;
    counter++;
}

int LocalCommand::getId() const{
    return id;
}

LocalCommandPrefix LocalCommand::getPrefix() const {
    return prefix;
}



bool LocalCommand::getBool() const{
    return boolValue;
}


void LocalCommand::setFloatValue(const float value) {
    floatValue = value;
}

void LocalCommand::setPrefix(LocalCommandPrefix globalCommandPrefix) {
    this->prefix = globalCommandPrefix;
}

void LocalCommand::setIntValue(int value) {
    this->intValue = value;
}
