//
// Created by gorod on 16.04.2026.
//

#include "ReleasePinHardware.h"


ReleasePinHardware::ReleasePinHardware(int pinNumber)
{
    initDebug(true, DEBUG_TEXT_PREFIX + std::to_string(pinNumber));
}

void ReleasePinHardware::setValue(float value)
{
    log("value set: " + std::to_string(value));
}

void ReleasePinHardware::enable(bool flag)
{
    ReleasePinHardware::enable(flag);
    if (flag) log("high level set");
    else log("low level set");
}

void ReleasePinHardware::complete()
{
    log("nothing to complete in software pin");
}

