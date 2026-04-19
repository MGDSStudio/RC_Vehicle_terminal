//
// Created by mgdsstudio on 18.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_QUARTER_H
#define RC_VEHICLE_TERMINAL_QUARTER_H

#include "GeometrieLibrary.h"
#include "TwoValuesStruct.h"
#include "../gamepad/InputConstants.h"
#include "../Logger.h"

enum class Quarter {
    LEFT_TOP, RIGHT_TOP, LEFT_BOTTOM, RIGHT_BOTTOM, DEAD_ZONE
};

class QuarterUtil {
public:
    static Quarter getForAngle(const float angle) {
        Quarter quarter;
        if (angle >= InputConstants::STICK_DEAD_ZONE_RIGHT_TOP && angle <= 90) quarter = Quarter::RIGHT_TOP;
        else if (angle > 90 && angle <= InputConstants::STICK_DEAD_ZONE_LEFT_TOP) quarter = Quarter::LEFT_TOP;
        else if (angle >= InputConstants::STICK_DEAD_ZONE_LEFT_BOTTOM && angle <= 270) quarter = Quarter::LEFT_BOTTOM;
        else if (angle >= 270 && angle <= InputConstants::STICK_DEAD_ZONE_RIGHT_BOTTOM) quarter = Quarter::RIGHT_BOTTOM;
        else quarter = Quarter::DEAD_ZONE;
        return quarter;
    }

    static float getRangeFromNullToOne (const float angle, Quarter quarter) {
        float range;
        if (quarter == Quarter::DEAD_ZONE) {
            Logger::criticalError("Wrong input for quarter at Quarter" );
            range = 0.0001;
        }
        else {
            if (quarter == Quarter::RIGHT_TOP) {
                range = GeometrieLibrary::map(angle, InputConstants::STICK_DEAD_ZONE_RIGHT_TOP, 90, 0, 1);
            }
            else if (quarter == Quarter::LEFT_TOP) {
                range = GeometrieLibrary::map(angle, InputConstants::STICK_DEAD_ZONE_LEFT_TOP, 90, 1,0);
            }
            else if (quarter == Quarter::LEFT_BOTTOM) {
                range = GeometrieLibrary::map(angle, InputConstants::STICK_DEAD_ZONE_LEFT_BOTTOM, 90, 0,1);
            }
            else {
                range = GeometrieLibrary::map(angle, InputConstants::STICK_DEAD_ZONE_RIGHT_BOTTOM, 90, 1,0);
            }
        }
        return range;
    }
};

#endif //RC_VEHICLE_TERMINAL_QUARTER_H

/*
static void getRangeFromNullToOne (const float angle, Quarter quarter, TwoValuesStruct* two_values_struct) {
        if (quarter == Quarter::DEAD_ZONE) {
            Logger::criticalError("Wrong input for quarter at Quarter" );
            two_values_struct->min = -1;
            two_values_struct->max = -1;
            return ;
        }
        else {
            if (quarter == Quarter::RIGHT_TOP) {
                two_values_struct->min = InputConstants::STICK_DEAD_ZONE_RIGHT_TOP;
                two_values_struct->max = 90;
            }
            else if (quarter == Quarter::LEFT_TOP) {
                two_values_struct->min = 90;
                two_values_struct->max = InputConstants::STICK_DEAD_ZONE_LEFT_TOP;
            }
        }
    }

*/