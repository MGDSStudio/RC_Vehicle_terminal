//
// Created by gorod on 16.04.2026.
//

#include "ReleasePinSoftware.h"

ReleasePinSoftware::ReleasePinSoftware(int pinNumber)
{
    initDebug(true, DEBUG_TEXT_PREFIX + std::to_string(pinNumber));
}

void ReleasePinSoftware::setValue(float value)
{
    log("value set: " + std::to_string(value));
}

void ReleasePinSoftware::enable(bool flag)
{
    ReleasePinSoftware::enable(flag);
    if (flag) log("high level set");
    else log("low level set");
}

void ReleasePinSoftware::complete()
{
    log("nothing to complete in software pin");
}


