//
// Created by mgdsstudio on 12.04.2026.
//

#include "WheelsSignalsCalculatorDigital.h"


void WheelsSignalsCalculatorDigital::applyMoveForward() const
{
    wheelForwardLeft->setForward();
    wheelForwardRight->setForward();
    wheelBackwardLeft->setForward();
    wheelBackwardRight->setForward();
}

void WheelsSignalsCalculatorDigital::applyMoveBackward() const
{
    wheelForwardLeft->setBackward();
    wheelForwardRight->setBackward();
    wheelBackwardLeft->setBackward();
    wheelBackwardRight->setBackward();
}

void WheelsSignalsCalculatorDigital::applyRotationCw() const
{
    wheelForwardLeft->setForward();
    wheelForwardRight->setBackward();
    wheelBackwardLeft->setForward();
    wheelBackwardRight->setBackward();
}

void WheelsSignalsCalculatorDigital::applyRotationCcw() const
{
    wheelForwardLeft->setBackward();
    wheelForwardRight->setForward();
    wheelBackwardLeft->setBackward();
    wheelBackwardRight->setForward();
}
