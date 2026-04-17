//
// Created by mgdsstudio on 12.04.2026.
//

#include "WheelsSignalsCalculatorSimple.h"

//constexpr static float DEAD_ZONE_NOMINAL = 0.15;
constexpr static float MIN_DEAD_ZONE_FOR_ROTATION = -0.95;
constexpr static float MAX_DEAD_ZONE_FOR_ROTATION = 0.95;

void WheelsSignalsCalculatorSimple::applyMoveForward(const float value) const {
    wheelForwardLeft->setForward(value);
    wheelForwardRight->setForward(value);
    wheelBackwardLeft->setForward(value);
    wheelBackwardRight->setForward(value);
}

void WheelsSignalsCalculatorSimple::applyMoveBackward(const float value) const {
    wheelForwardLeft->setBackward(value);
    wheelForwardRight->setBackward(value);
    wheelBackwardLeft->setBackward(value);
    wheelBackwardRight->setBackward(value);
}

void WheelsSignalsCalculatorSimple::applyRotationCw(const float value) const {
    if (value >= MAX_DEAD_ZONE_FOR_ROTATION){
        wheelForwardLeft->setForward(value);
        wheelForwardRight->setBackward(value);
        wheelBackwardLeft->setForward(value);
        wheelBackwardRight->setBackward(value);
    }
}

void WheelsSignalsCalculatorSimple::applyRotationCcw(const float value) const {
    if (value <= MIN_DEAD_ZONE_FOR_ROTATION){
        wheelForwardLeft->setBackward(value);
        wheelForwardRight->setForward(value);
        wheelBackwardLeft->setBackward(value);
        wheelBackwardRight->setForward(value);
    }
}

void WheelsSignalsCalculatorSimple::stopAll() const {
    wheelForwardLeft->stop();
    wheelForwardRight->stop();
    wheelBackwardLeft->stop();
    wheelBackwardRight->stop();
}
