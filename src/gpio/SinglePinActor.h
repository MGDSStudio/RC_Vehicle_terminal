//
// Created by Alexander on 09.04.2026.
//

#ifndef RC_VEHICLE_WHEEL_H
#define RC_VEHICLE_WHEEL_H


#include "Pin.h"
#include "PinCommon.h"
#include "ReleasePin.h"

class SinglePinActor {

public:
    SinglePinActor(ReleasePin* pin){
        this->softwarePin = pin;
    }

    SinglePinActor(){

    }

    ~SinglePinActor(){
        this->softwarePin = nullptr;
        hardwarePin = nullptr;
        Logger::debug("Maybe delete manually at SinglePinActor");
    }

    void setSoftwarePin(ReleasePin* pin);

    void setValue(float value) const;
    
    void enable(bool flag) const;

    void complete() const;

    void setHardwarePin(ReleasePin* pin_common);

private:
    ReleasePin* softwarePin = nullptr;
    ReleasePin* hardwarePin = nullptr;
    //PinCommon* pinCommon = nullptr;
    float direction;
};


#endif //RC_VEHICLE_WHEEL_H
