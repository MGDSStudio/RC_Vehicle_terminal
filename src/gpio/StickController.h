//
// Created by gorod on 14.04.2026.
//

#ifndef CMAKESFMLPROJECT_STICKCONTROLLER_H
#define CMAKESFMLPROJECT_STICKCONTROLLER_H
#include "AnalogMovementCalculator.h"
#include "TouchPlace.h"
#include "WheelsControlDataStruct.h"


class StickController
{

public:
    StickController();
    ~StickController() = default;

    void setX(const float x)
    {
        touch_place.setX(x);
    }

    void setY(float y)
    {
        touch_place.setY(y);
    }

    bool updateDataStruct(WheelsControlDataStruct* wheels_control_data_struct)
    {
        if (touch_place.wasPlaceUpdated())
        {
            float angle = touch_place.getAngle();
            float radius = touch_place.getRadius();
            analog_movement_calculator.updateDataStruct(wheels_control_data_struct, angle,radius);
            return true;
        }
        else {
            //Logger::debug("touch place is same");
            return false;
        }
    }

private:
    static constexpr float DEAD_ZONE_ANGLE = 25;
    TouchPlace touch_place {1,25};
    bool inDeadZone = true;
    bool placeUpdated;
    AnalogMovementCalculator analog_movement_calculator;
};


#endif //CMAKESFMLPROJECT_STICKCONTROLLER_H