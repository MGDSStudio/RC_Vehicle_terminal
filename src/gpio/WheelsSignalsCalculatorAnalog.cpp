//
// Created by gorod on 17.04.2026.
//

#include "WheelsSignalsCalculatorAnalog.h"

//constexpr static float DEAD_ZONE_NOMINAL = 0.15;
constexpr static float MIN_DEAD_ZONE_FOR_ROTATION = -0.95;
constexpr static float MAX_DEAD_ZONE_FOR_ROTATION = 0.95;




void WheelsSignalsCalculatorAnalog::applyMovement(float valueBetweenMinusOneAndOne) {
    this->stick_controller.setY(valueBetweenMinusOneAndOne);

}

void WheelsSignalsCalculatorAnalog::applyRotation(const float valueBetweenMinusOneAndOne) {
    this->stick_controller.setX(valueBetweenMinusOneAndOne);
}



