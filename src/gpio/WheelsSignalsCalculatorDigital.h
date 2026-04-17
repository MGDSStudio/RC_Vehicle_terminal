
//
// Created by mgdsstudio on 12.04.2026.
//

#ifndef CMAKESFMLPROJECT_WHEELSIGNALSCALCULATOR_H
#define CMAKESFMLPROJECT_WHEELSIGNALSCALCULATOR_H

#include "WheelActor.h"
#include "IWheelsSignalsCalculator.h"
#include "../Constants.h"
#include "../GeometrieLibrary.h"



class WheelsSignalsCalculatorDigital  : public IWheelsSignalsCalculator{

public:
    WheelsSignalsCalculatorDigital(WheelActor* wheel_forward_left, WheelActor* wheel_forward_right, WheelActor* wheel_backward_left, WheelActor* wheel_backward_right) : IWheelsSignalsCalculator(wheel_forward_left, wheel_forward_right, wheel_backward_left, wheel_backward_right)
    {

    }

    ~WheelsSignalsCalculatorDigital() override = default;

    void applyMoveForward() const;
    void applyMoveBackward() const;
    void applyRotationCw() const;
    void applyRotationCcw() const;

protected:
    static int getMappedAxisValue(float betweenMinusOneAndOne)
    {
        float mapped = GeometrieLibrary::map(betweenMinusOneAndOne, Constants::MIN_ANALOG_VALUE, Constants::MAX_ANALOG_VALUE, Constants::MIN_EFFECTIVE_PWM_VALUE_FOR_MAX_VALUE, Constants::MAX_EFFECTIVE_PWM_VALUE_FOR_MIN_VALUE);
        return static_cast<int>(Constants::MAX_EFFECTIVE_PWM_VALUE_FOR_MIN_VALUE-mapped);
    }
    static constexpr int STOP_VALUE = 0;

};


#endif //CMAKESFMLPROJECT_WHEELSIGNALSCALCULATOR_H