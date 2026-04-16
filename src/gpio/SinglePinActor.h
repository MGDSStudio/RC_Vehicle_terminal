//
// Created by Alexander on 09.04.2026.
//

#ifndef RC_VEHICLE_WHEEL_H
#define RC_VEHICLE_WHEEL_H


#include "Pin.h"
#include "PinCommon.h"

class SinglePinActor {

public:
    SinglePinActor(Pin* pin){
        this->softwareDebugOnlyPin = pin;
    }

    SinglePinActor(){

    }

    ~SinglePinActor(){
        this->softwareDebugOnlyPin = nullptr;
        pinCommon = nullptr;
    }

    void setPin(Pin* pin);

    void setValue(float value) const;
    
    void enable(bool flag) const;

    void complete() const;

    void setPinCommon(PinCommon* pin_common);

private:
    Pin* softwareDebugOnlyPin = nullptr;
    PinCommon* pinCommon = nullptr;
    float direction;
};


#endif //RC_VEHICLE_WHEEL_H
