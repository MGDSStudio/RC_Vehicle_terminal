//
// Created by Alexander on 09.04.2026.
//

#include "WheelActor.h"


WheelActor::WheelActor() {

}


void WheelActor::setForward(float relativeValue) {
    softwarePinForward->setValue(relativeValue);
    softwarePinBackward->enable(false);
    hardwarePinForward->setValue(relativeValue);
    hardwarePinBackward->enable(false);
    this->direction = relativeValue;
}

void WheelActor::setBackward(float relativeValue) {
    softwarePinForward->enable(false);
    softwarePinBackward->setValue(relativeValue);
    hardwarePinForward->enable(false);
    hardwarePinBackward->setValue(relativeValue);
    this->direction = relativeValue;
}

void WheelActor::stop() {
    softwarePinForward->enable(false);
    softwarePinBackward->enable(false);
    hardwarePinForward->enable(false);
    hardwarePinBackward->enable(false);
    this->direction = 0;
}

void WheelActor::setPinForward(ReleasePin* pin){
    this->softwarePinForward = pin;
}

void WheelActor::setPinBackward(ReleasePin* pin){
    this->softwarePinBackward = pin;
}

void WheelActor::setHardwarePinForward(ReleasePin *pin) {
    this->hardwarePinForward = pin;
}

void WheelActor::setHardwarePinBackward(ReleasePin *pin) {
    this->hardwarePinBackward = pin;
}

