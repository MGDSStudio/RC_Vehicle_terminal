//
// Created by gorod on 17.04.2026.
//

#include "WheelsSignalsCalculatorAnalog.h"

void WheelsSignalsCalculatorAnalog::applyMoveForward(float valueBetweenMinusOneAndOne) const {
    if (valueBetweenMinusOneAndOne < Constants::NEUTRAL_ANALOG_VALUE) valueBetweenMinusOneAndOne = Constants::NEUTRAL_ANALOG_VALUE;
    wheelForwardLeft->setForward(valueBetweenMinusOneAndOne);
    wheelForwardRight->setForward(valueBetweenMinusOneAndOne);
    wheelBackwardLeft->setForward(valueBetweenMinusOneAndOne);
    wheelBackwardRight->setForward(valueBetweenMinusOneAndOne);
}

void WheelsSignalsCalculatorAnalog::applyMoveBackward(float valueBetweenMinusOneAndOne) const {
    wheelForwardLeft->setBackward(valueBetweenMinusOneAndOne);
    wheelForwardRight->setBackward(valueBetweenMinusOneAndOne);
    wheelBackwardLeft->setBackward(valueBetweenMinusOneAndOne);
    wheelBackwardRight->setBackward(valueBetweenMinusOneAndOne);
}

void WheelsSignalsCalculatorAnalog::applyRotation(const float valueBetweenMinusOneAndOne) const {
    wheelForwardLeft->setForward(valueBetweenMinusOneAndOne);
    wheelForwardRight->setBackward(valueBetweenMinusOneAndOne);
    wheelBackwardLeft->setForward(valueBetweenMinusOneAndOne);
    wheelBackwardRight->setBackward(valueBetweenMinusOneAndOne);
}