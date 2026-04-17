
//
// Created by mgdsstudio on 12.04.2026.
//

#ifndef CMAKESFMLPROJECT_WHEELSIGNALSCALCULATOR_H
#define CMAKESFMLPROJECT_WHEELSIGNALSCALCULATOR_H

#include "WheelActor.h"
#include "../Constants.h"
#include "../GeometrieLibrary.h"

class WheelsSignalsCalculatorSimple {


enum class ActivationType{
    ANALOG, DIGITAL, NO_DATA
};

public:
    WheelsSignalsCalculatorSimple(WheelActor* wheelForwardLeft, WheelActor* wheelForwardRight, WheelActor* wheelBackwardLeft, WheelActor* wheelBackwardRight) {
        this->wheelForwardLeft = wheelForwardLeft;
        this->wheelForwardRight = wheelForwardRight;
        this->wheelBackwardLeft = wheelBackwardLeft;
        this->wheelBackwardRight = wheelBackwardRight;
    }
    void applyMoveForward();
    void applyMoveBackward();
    void applyRotationCw();
    void applyRotationCcw();

    void applyMoveForward(float valueBetweenMinusOneAndOne) const;

    void applyMoveBackward(float valueBetweenMinusOneAndOne) const;

    void applyRotationCw(float valueBetweenMinusOneAndOne) const;

    void applyRotationCcw(float valueBetweenMinusOneAndOne) const;

    void stopAll() const;

private:
    WheelActor* wheelForwardLeft;
    WheelActor* wheelForwardRight;
    WheelActor* wheelBackwardLeft;
    WheelActor* wheelBackwardRight;
    ActivationType actualActivationType = ActivationType::NO_DATA;

    static int getMappedAxisValue(float betweenMinusOneAndOne)
    {
        float mapped = GeometrieLibrary::map(betweenMinusOneAndOne, Constants::MIN_ANALOG_VALUE, Constants::MAX_ANALOG_VALUE, Constants::MIN_EFFECTIVE_PWM_VALUE_FOR_MAX_VALUE, Constants::MAX_EFFECTIVE_PWM_VALUE_FOR_MIN_VALUE);
        return static_cast<int>(Constants::MAX_EFFECTIVE_PWM_VALUE_FOR_MIN_VALUE-mapped);
    }
    static constexpr int STOP_VALUE = 0;
};


#endif //CMAKESFMLPROJECT_WHEELSIGNALSCALCULATOR_H