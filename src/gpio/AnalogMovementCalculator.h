//
// Created by gorod on 17.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_ANALOGMOVEMENTCALCULATOR_H
#define RC_VEHICLE_TERMINAL_ANALOGMOVEMENTCALCULATOR_H
#include "WheelsControlDataStruct.h"
#include "../Constants.h"
#include "../libs/Quarter.h"


class AnalogMovementCalculator
{

public:
    void updateDataStruct(WheelsControlDataStruct* wheels_control_data_struct, float angle, float radiusFromNullToOne)
    {
        auto quarter = QuarterUtil::getForAngle(angle);
        float mappedAngle = QuarterUtil::getRangeFromNullToOne(angle, quarter);
        float mappedVelociy;
        if (radiusFromNullToOne<MIN_ANALOG_VALUE_FOR_WHEEL) mappedVelociy = 0;
        else mappedVelociy = GeometrieLibrary::map(radiusFromNullToOne, 0, 1, MIN_ANALOG_VALUE_FOR_WHEEL, MAX_ANALOG_VALUE_FOR_WHEEL);
        float maxVelocity = mappedVelociy;
        float minVelocity = mappedVelociy*mappedAngle;
        if (debug) Logger::debug("Mapped angle "+ std::to_string(mappedAngle) + "; source angle was: " + std::to_string(angle) + "quarter: " + QuarterUtil::getQuarterName(quarter));

        if (quarter == Quarter::RIGHT_TOP) {
            wheels_control_data_struct->frontRight = minVelocity;
            wheels_control_data_struct->rearRight = minVelocity;
            wheels_control_data_struct->frontLeft = maxVelocity;;
            wheels_control_data_struct->rearLeft = maxVelocity;
        }
        else if (quarter == Quarter::LEFT_TOP) {
            wheels_control_data_struct->frontRight = maxVelocity;
            wheels_control_data_struct->rearRight = maxVelocity;
            wheels_control_data_struct->frontLeft = minVelocity;
            wheels_control_data_struct->rearLeft = minVelocity;
        }
        else if (quarter == Quarter::RIGHT_BOTTOM) {
            wheels_control_data_struct->frontRight = -minVelocity;
            wheels_control_data_struct->rearRight = -minVelocity;
            wheels_control_data_struct->frontLeft = -maxVelocity;
            wheels_control_data_struct->rearLeft = -maxVelocity;
        }
        else if (quarter == Quarter::LEFT_BOTTOM) {
            wheels_control_data_struct->frontRight = -maxVelocity;
            wheels_control_data_struct->rearRight = -maxVelocity;
            wheels_control_data_struct->frontLeft = -minVelocity;
            wheels_control_data_struct->rearLeft = -minVelocity;
        }
    }

private:
    inline static bool debug = true;
    constexpr static float MAX_ANALOG_VALUE_FOR_WHEEL = Constants::MAX_ANALOG_VALUE;
    constexpr static float MIN_ANALOG_VALUE_FOR_WHEEL = 2*Constants::MIN_EFFECTIVE_ANALOG_VALUE;
};


#endif //RC_VEHICLE_TERMINAL_ANALOGMOVEMENTCALCULATOR_H

/*
void updateDataStruct(WheelsControlDataStruct* wheels_control_data_struct, float angle, float radiusFromNullToOne)
    {
        auto quarter = QuarterUtil::getForAngle(angle);
        float mappedAngle = QuarterUtil::getRangeFromNullToOne(angle, quarter);
         float mappedVelociy;
        if (radiusFromNullToOne<MIN_ANALOG_VALUE_FOR_WHEEL) mappedVelociy = 0;
        else mappedVelociy = GeometrieLibrary::map(radiusFromNullToOne, 0, 1, MIN_ANALOG_VALUE_FOR_WHEEL, MAX_ANALOG_VALUE_FOR_WHEEL);
        float maxVelocity = mappedVelociy;
        float minVelocity = mappedVelociy*mappedAngle;
        if (debug) Logger::debug("Mapped angle "+ std::to_string(mappedAngle) + "source angle was: " + std::to_string(angle));

        if (quarter == Quarter::RIGHT_TOP) {
            wheels_control_data_struct->frontRight = minVelocity;
            wheels_control_data_struct->rearRight = minVelocity;
            wheels_control_data_struct->frontLeft = maxVelocity;;
            wheels_control_data_struct->rearLeft = maxVelocity;
        }
        else if (quarter == Quarter::LEFT_TOP) {
            wheels_control_data_struct->frontRight = maxVelocity;
            wheels_control_data_struct->rearRight = maxVelocity;
            wheels_control_data_struct->frontLeft = minVelocity;
            wheels_control_data_struct->rearLeft = minVelocity;
        }
        else if (quarter == Quarter::RIGHT_BOTTOM) {
            wheels_control_data_struct->frontRight = minVelocity;
            wheels_control_data_struct->rearRight = minVelocity;
            wheels_control_data_struct->frontLeft = maxVelocity;
            wheels_control_data_struct->rearLeft = maxVelocity;
        }
        else if (quarter == Quarter::LEFT_BOTTOM) {
            wheels_control_data_struct->frontRight = maxVelocity;
            wheels_control_data_struct->rearRight = maxVelocity;
            wheels_control_data_struct->frontLeft = minVelocity;
            wheels_control_data_struct->rearLeft = minVelocity;
        }


    }

*/