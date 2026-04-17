//
// Created by mgdsstudio on 12.04.2026.
//

#include "WheelsSignalsCalculatorDigital.h"

//constexpr static float DEAD_ZONE_NOMINAL = 0.15;
constexpr static float MIN_DEAD_ZONE_FOR_ROTATION = -0.95;
constexpr static float MAX_DEAD_ZONE_FOR_ROTATION = 0.95;

void WheelsSignalsCalculatorDigital::applyMoveForward()
{
    wheelForwardLeft->setForward();
    wheelForwardRight->setForward();
    wheelBackwardLeft->setForward();
    wheelBackwardRight->setForward();
}

void WheelsSignalsCalculatorDigital::applyMoveBackward()
{
    wheelForwardLeft->setBackward();
    wheelForwardRight->setBackward();
    wheelBackwardLeft->setBackward();
    wheelBackwardRight->setBackward();
}

void WheelsSignalsCalculatorDigital::applyRotationCw()
{
    wheelForwardLeft->setForward();
    wheelForwardRight->setBackward();
    wheelBackwardLeft->setForward();
    wheelBackwardRight->setBackward();
}

void WheelsSignalsCalculatorDigital::applyRotationCcw()
{
    wheelForwardLeft->setBackward();
    wheelForwardRight->setForward();
    wheelBackwardLeft->setBackward();
    wheelBackwardRight->setForward();
}

void WheelsSignalsCalculatorDigital::applyMoveForward(float valueBetweenMinusOneAndOne) const {
    if (valueBetweenMinusOneAndOne < Constants::NEUTRAL_ANALOG_VALUE) valueBetweenMinusOneAndOne = Constants::NEUTRAL_ANALOG_VALUE;
    wheelForwardLeft->setForward(valueBetweenMinusOneAndOne);
    wheelForwardRight->setForward(valueBetweenMinusOneAndOne);
    wheelBackwardLeft->setForward(valueBetweenMinusOneAndOne);
    wheelBackwardRight->setForward(valueBetweenMinusOneAndOne);
}

void WheelsSignalsCalculatorDigital::applyMoveBackward(float valueBetweenMinusOneAndOne) const {
    wheelForwardLeft->setBackward(valueBetweenMinusOneAndOne);
    wheelForwardRight->setBackward(valueBetweenMinusOneAndOne);
    wheelBackwardLeft->setBackward(valueBetweenMinusOneAndOne);
    wheelBackwardRight->setBackward(valueBetweenMinusOneAndOne);
}

void WheelsSignalsCalculatorDigital::applyRotationCw(const float valueBetweenMinusOneAndOne) const {
    if (valueBetweenMinusOneAndOne >= MAX_DEAD_ZONE_FOR_ROTATION){
        wheelForwardLeft->setForward(valueBetweenMinusOneAndOne);
        wheelForwardRight->setBackward(valueBetweenMinusOneAndOne);
        wheelBackwardLeft->setForward(valueBetweenMinusOneAndOne);
        wheelBackwardRight->setBackward(valueBetweenMinusOneAndOne);
    }
}

void WheelsSignalsCalculatorDigital::applyRotationCcw(const float valueBetweenMinusOneAndOne) const {
    if (valueBetweenMinusOneAndOne <= MIN_DEAD_ZONE_FOR_ROTATION){
        wheelForwardLeft->setBackward(valueBetweenMinusOneAndOne);
        wheelForwardRight->setForward(valueBetweenMinusOneAndOne);
        wheelBackwardLeft->setBackward(valueBetweenMinusOneAndOne);
        wheelBackwardRight->setForward(valueBetweenMinusOneAndOne);
    }
}


