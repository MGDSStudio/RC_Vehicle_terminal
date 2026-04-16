//
// Created by Alexander on 09.04.2026.
//

#include "SinglePinActor.h"




void SinglePinActor::setPin(Pin* pin){
    this->softwareDebugOnlyPin = pin;
}

void SinglePinActor::setValue(float value) const {
    softwareDebugOnlyPin->setValue(value);
    pinCommon->setValue(value);
}
    
void SinglePinActor::enable(bool flag) const {
    softwareDebugOnlyPin->enable(flag);
    pinCommon->enable(flag);
}

void SinglePinActor::complete() const {
    softwareDebugOnlyPin->complete();
    pinCommon->complete();
}



void SinglePinActor::setPinCommon(PinCommon *pin_common) {
    this->pinCommon = pin_common;
}
