//
// Created by Alexander on 09.04.2026.
//

#include "SinglePinActor.h"

void SinglePinActor::setSoftwarePin(ReleasePin* pin){
    this->softwarePin = pin;
}

void SinglePinActor::setValue(float value) const {
    softwarePin->setValue(value);
    hardwarePin->setValue(value);
}
    
void SinglePinActor::enable(bool flag) const {
    softwarePin->enable(flag);
    hardwarePin->enable(flag);
}

void SinglePinActor::complete() const {
    softwarePin->complete();
    hardwarePin->complete();
}



void SinglePinActor::setHardwarePin(ReleasePin *pin_common) {
    this->hardwarePin = pin_common;
}
