//
// Created by gorod on 17.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_WHEELSSIGNALSCALCULATORANALOG_H
#define RC_VEHICLE_TERMINAL_WHEELSSIGNALSCALCULATORANALOG_H
#include "IWheelsSignalsCalculator.h"
#include "StickController.h"
#include "../Constants.h"

#include "WheelsControlDataStruct.h"

class WheelsSignalsCalculatorAnalog : public IWheelsSignalsCalculator
{

public:
    WheelsSignalsCalculatorAnalog(WheelActor* wheel_forward_left, WheelActor* wheel_forward_right, WheelActor* wheel_backward_left, WheelActor* wheel_backward_right) : IWheelsSignalsCalculator(wheel_forward_left, wheel_forward_right, wheel_backward_left, wheel_backward_right)
    {

    }

    WheelsSignalsCalculatorAnalog() : IWheelsSignalsCalculator() {
        Logger::debug("Test launched at WheelsSignalsCalculatorAnalog");
        testing = true;
    }

    ~WheelsSignalsCalculatorAnalog() override = default;

    void applyMovement(float valueBetweenMinusOneAndOne);

    void applyRotation(float valueBetweenMinusOneAndOne);
    void setValue(float value, WheelActor* wheel_actor) const;
    void update();

    WheelsControlDataStruct get_wheels_control_data_struct_test_only() const {
        return wheels_control_data_struct;
    }

    std::string get_text_representation() {
        std::string  text;
        text+="Front left:";
        text+=std::to_string(wheels_control_data_struct.frontLeft);
        text+="; Front right:";
        text+=std::to_string(wheels_control_data_struct.frontRight);
        text+="; Rear left:";
        text+=std::to_string(wheels_control_data_struct.rearLeft);
        text+="; Rear right:";
        text+=std::to_string(wheels_control_data_struct.rearRight);
        return text;
    }


private:
    inline static bool testing = false;
    inline static bool enableAnalogControl = true;
    inline static bool debug = true;
    inline static float DEAD_ZONE_MAX = 0.15f;
    inline static float DEAD_ZONE_MIN = -DEAD_ZONE_MAX;
    WheelsControlDataStruct wheels_control_data_struct;
    StickController stick_controller;
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


};


#endif //RC_VEHICLE_TERMINAL_WHEELSSIGNALSCALCULATORANALOG_H