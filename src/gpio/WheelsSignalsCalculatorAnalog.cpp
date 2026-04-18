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

void WheelsSignalsCalculatorAnalog::update()
{
    if (enableAnalogControl)
    {
        bool wasUpdated = this->stick_controller.updateDataStruct(&wheels_control_data_struct);
        if (wasUpdated){
            if (!testing) {
                setValue(wheels_control_data_struct.frontLeft, wheelForwardLeft);
                setValue(wheels_control_data_struct.frontRight, wheelForwardRight);
                setValue(wheels_control_data_struct.rearLeft, wheelBackwardLeft);
                setValue(wheels_control_data_struct.rearRight, wheelBackwardRight);
            }
        }
    }
}

void WheelsSignalsCalculatorAnalog::setValue(float value, WheelActor* wheel_actor) const
{
    if ( value>DEAD_ZONE_MAX)
    {
        wheel_actor->setForward(wheels_control_data_struct.frontLeft);
    }
    else if ( value<DEAD_ZONE_MIN)
    {
        wheel_actor->setBackward(-value);
    }
    else wheel_actor->stop();
}




