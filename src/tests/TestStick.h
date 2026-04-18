//
// Created by mgdsstudio on 18.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_TESTSTICK_H
#define RC_VEHICLE_TERMINAL_TESTSTICK_H

#include "../gpio/WheelsSignalsCalculatorAnalog.h"

class TestStick {

public:
    TestStick() {

        test(0.85, 1);
        test(0.7, 1);
        test(0.1, 1);

        test(1, 0.5);
        test(0.9, 0.5);
        test(-0.9, 0.5);
    }

    void test(float x, float y){
        wheels_signals_calculator_analog.applyMovement(y);
        wheels_signals_calculator_analog.applyRotation(x);
        wheels_signals_calculator_analog.update();
        Logger::debug("Test place: " + wheels_signals_calculator_analog.get_text_representation());
    }

private:
    WheelsSignalsCalculatorAnalog wheels_signals_calculator_analog;

};


#endif //RC_VEHICLE_TERMINAL_TESTSTICK_H