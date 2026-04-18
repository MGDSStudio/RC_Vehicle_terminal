//
// Created by Alexander on 09.04.2026.
//

#include "WheelActor.h"

#ifdef IS_RPI
    inline static bool isRpi = true;
#else
inline static bool isRpi = false;
#endif

WheelActor::WheelActor() {

}


void WheelActor::setForward(float relativeValue) {
    if (!isRpi) {
        softwarePinForward->setValue(relativeValue);
        softwarePinBackward->enable(false);
    }
    hardwarePinForward->setValue(relativeValue);
    hardwarePinBackward->enable(false);
    this->direction = relativeValue;
}

void WheelActor::setBackward(float relativeValue) {
    if (!isRpi) {
        softwarePinForward->enable(false);
        softwarePinBackward->setValue(relativeValue);
    }

    hardwarePinForward->enable(false);
    hardwarePinBackward->setValue(relativeValue);
    this->direction = relativeValue;
}

void WheelActor::stop() {
    if (!isRpi) {
        softwarePinForward->enable(false);
        softwarePinBackward->enable(false);
    }
    hardwarePinForward->enable(false);
    hardwarePinBackward->enable(false);
    this->direction = 0;
}

void WheelActor::setForward()
{
    if (!isRpi) {
        softwarePinForward->enable(true);
        softwarePinBackward->enable(false);
    }

    hardwarePinForward->enable(true);

    hardwarePinBackward->enable(false);
}

void WheelActor::setBackward()
{
    if (!isRpi) {
        softwarePinForward->enable(false);
        softwarePinBackward->enable(true);
    }

    hardwarePinForward->enable(false);

    hardwarePinBackward->enable(true);
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

