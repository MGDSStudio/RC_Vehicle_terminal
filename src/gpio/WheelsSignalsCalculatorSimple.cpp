//
// Created by mgdsstudio on 12.04.2026.
//

#include "WheelsSignalsCalculatorSimple.h"

//constexpr static float DEAD_ZONE_NOMINAL = 0.15;
constexpr static float MIN_DEAD_ZONE_FOR_ROTATION = -0.95;
constexpr static float MAX_DEAD_ZONE_FOR_ROTATION = 0.95;

void WheelsSignalsCalculatorSimple::applyMoveForward()
{

}

void WheelsSignalsCalculatorSimple::applyMoveBackward()
{
}

void WheelsSignalsCalculatorSimple::applyRotationCw()
{
}

void WheelsSignalsCalculatorSimple::applyRotationCcw()
{
}

void WheelsSignalsCalculatorSimple::applyMoveForward(float valueBetweenMinusOneAndOne) const {
    if (valueBetweenMinusOneAndOne < Constants::NEUTRAL_ANALOG_VALUE) valueBetweenMinusOneAndOne = Constants::NEUTRAL_ANALOG_VALUE;
    wheelForwardLeft->setForward(valueBetweenMinusOneAndOne);
    wheelForwardRight->setForward(valueBetweenMinusOneAndOne);
    wheelBackwardLeft->setForward(valueBetweenMinusOneAndOne);
    wheelBackwardRight->setForward(valueBetweenMinusOneAndOne);
}

void WheelsSignalsCalculatorSimple::applyMoveBackward(float valueBetweenMinusOneAndOne) const {
    wheelForwardLeft->setBackward(valueBetweenMinusOneAndOne);
    wheelForwardRight->setBackward(valueBetweenMinusOneAndOne);
    wheelBackwardLeft->setBackward(valueBetweenMinusOneAndOne);
    wheelBackwardRight->setBackward(valueBetweenMinusOneAndOne);
}

void WheelsSignalsCalculatorSimple::applyRotationCw(const float valueBetweenMinusOneAndOne) const {
    if (valueBetweenMinusOneAndOne >= MAX_DEAD_ZONE_FOR_ROTATION){
        wheelForwardLeft->setForward(valueBetweenMinusOneAndOne);
        wheelForwardRight->setBackward(valueBetweenMinusOneAndOne);
        wheelBackwardLeft->setForward(valueBetweenMinusOneAndOne);
        wheelBackwardRight->setBackward(valueBetweenMinusOneAndOne);
    }
}

void WheelsSignalsCalculatorSimple::applyRotationCcw(const float valueBetweenMinusOneAndOne) const {
    if (valueBetweenMinusOneAndOne <= MIN_DEAD_ZONE_FOR_ROTATION){
        wheelForwardLeft->setBackward(valueBetweenMinusOneAndOne);
        wheelForwardRight->setForward(valueBetweenMinusOneAndOne);
        wheelBackwardLeft->setBackward(valueBetweenMinusOneAndOne);
        wheelBackwardRight->setForward(valueBetweenMinusOneAndOne);
    }
}

void WheelsSignalsCalculatorSimple::stopAll() const {
    wheelForwardLeft->stop();
    wheelForwardRight->stop();
    wheelBackwardLeft->stop();
    wheelBackwardRight->stop();
}
