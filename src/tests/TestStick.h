//
// Created by mgdsstudio on 18.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_TESTSTICK_H
#define RC_VEHICLE_TERMINAL_TESTSTICK_H

#include "../gpio/WheelsSignalsCalculatorAnalog.h"

class TestStick {

public:
    TestStick() {
        WheelsSignalsCalculatorAnalog wheels_signals_calculator_analog;
        wheels_signals_calculator_analog.applyMovement(1);
        wheels_signals_calculator_analog.applyRotation(0.01);
        wheels_signals_calculator_analog.update();
        Logger::debug("Test place: " + wheels_signals_calculator_analog.get_text_representation());
    }

};


#endif //RC_VEHICLE_TERMINAL_TESTSTICK_H