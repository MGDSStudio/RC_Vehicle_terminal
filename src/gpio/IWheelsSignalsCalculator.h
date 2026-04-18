//
// Created by gorod on 17.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_WHEELSSIGNALSCALCULATOR_H
#define RC_VEHICLE_TERMINAL_WHEELSSIGNALSCALCULATOR_H
#include "WheelActor.h"


class IWheelsSignalsCalculator
{

public:
    IWheelsSignalsCalculator(WheelActor* wheelForwardLeft, WheelActor* wheelForwardRight, WheelActor* wheelBackwardLeft, WheelActor* wheelBackwardRight) {
        this->wheelForwardLeft = wheelForwardLeft;
        this->wheelForwardRight = wheelForwardRight;
        this->wheelBackwardLeft = wheelBackwardLeft;
        this->wheelBackwardRight = wheelBackwardRight;
    }

    IWheelsSignalsCalculator() {
        /*this->wheelForwardLeft = wheelForwardLeft;
        this->wheelForwardRight = wheelForwardRight;
        this->wheelBackwardLeft = wheelBackwardLeft;
        this->wheelBackwardRight = wheelBackwardRight;*/
    }

    virtual ~IWheelsSignalsCalculator() = default;

    virtual void stopAll() const final {
        wheelForwardLeft->stop();
        wheelForwardRight->stop();
        wheelBackwardLeft->stop();
        wheelBackwardRight->stop();
    }

protected:
    WheelActor* wheelForwardLeft;
    WheelActor* wheelForwardRight;
    WheelActor* wheelBackwardLeft;
    WheelActor* wheelBackwardRight;
};


#endif //RC_VEHICLE_TERMINAL_WHEELSSIGNALSCALCULATOR_H