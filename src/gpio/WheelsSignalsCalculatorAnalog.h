//
// Created by gorod on 17.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_WHEELSSIGNALSCALCULATORANALOG_H
#define RC_VEHICLE_TERMINAL_WHEELSSIGNALSCALCULATORANALOG_H
#include "IWheelsSignalsCalculator.h"
#include "../Constants.h"
#include "StickController.h"

class WheelsSignalsCalculatorAnalog : public IWheelsSignalsCalculator
{

public:
    WheelsSignalsCalculatorAnalog(WheelActor* wheel_forward_left, WheelActor* wheel_forward_right, WheelActor* wheel_backward_left, WheelActor* wheel_backward_right) : IWheelsSignalsCalculator(wheel_forward_left, wheel_forward_right, wheel_backward_left, wheel_backward_right)
    {

    }

    ~WheelsSignalsCalculatorAnalog() override = default;

    void applyMovement(float valueBetweenMinusOneAndOne);

    void applyRotation(float valueBetweenMinusOneAndOne);

private:
    inline static bool debug = true;
    static void logNotImplemented()
    {
        log("not implemented");
    }

    static void log(std::string message)
    {
        if (debug)
        {
            Logger::custom("WheelsSignalsCalculatorAnalog", message);
        }
    }

    StickController stick_controller;
};


#endif //RC_VEHICLE_TERMINAL_WHEELSSIGNALSCALCULATORANALOG_H