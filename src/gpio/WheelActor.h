//
// Created by Alexander on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_WHEELACTOR_H
#define CMAKESFMLPROJECT_WHEELACTOR_H


#include "SinglePinActor.h"
#include "magic_enum/magic_enum.hpp"



class WheelActor{

public:
    WheelActor();

    ~WheelActor(){
        delete softwarePinForward;
        delete softwarePinBackward;
        delete hardwarePinForward;
        delete hardwarePinBackward;
    }
    void setPinForward(ReleasePin* pin);
    void setPinBackward(ReleasePin* pin);
    void setHardwarePinForward(ReleasePin* pin);
    void setHardwarePinBackward(ReleasePin* pin);

    void setForward(float relativeValue);
    void setBackward(float relativeValue);
    void stop();

private:
    ReleasePin* softwarePinForward = nullptr;
    ReleasePin* softwarePinBackward = nullptr;
    ReleasePin* hardwarePinForward = nullptr;
    ReleasePin* hardwarePinBackward = nullptr;
    float direction;
};


#endif //CMAKESFMLPROJECT_WHEELACTOR_H
