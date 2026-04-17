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

    void setY(float x)
    {
        touch_place.setX(x);
    }

    void updateDataStruct(WheelsControlDataStruct* wheels_control_data_struct)
    {
        if (touch_place.wasPlaceUpdated())
        {
            analog_movement_calculator.updateDataStruct(wheels_control_data_struct, 1,1);
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