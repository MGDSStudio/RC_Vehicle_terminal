//
// Created by gorod on 14.04.2026.
//

#ifndef CMAKESFMLPROJECT_STICKCONTROLLER_H
#define CMAKESFMLPROJECT_STICKCONTROLLER_H
#include "TouchPlace.h"
#include "WheelsControlDataStruct.h"
#include "WheelsSignalsCalculatorAnalog.h"


class StickController
{

public:
    StickController() = default;
    ~StickController() = default;

    void setX(const float x)
    {
        touch_place.setX(x);
    }

    void setY(float x)
    {
        touch_place.setX(x);
    }

    void update()
    {
        if (touch_place.wasPlaceUpdated())
        {

        }
    }

    void updateDataStruct(WheelsControlDataStruct* wheels_control_data_struct)
    {
        if (touch_place.wasPlaceUpdated())
        {

        }
    }

private:
    static constexpr float DEAD_ZONE_ANGLE = 25;
    TouchPlace touch_place {1,25};
    bool inDeadZone = true;
    bool placeUpdated;
};


#endif //CMAKESFMLPROJECT_STICKCONTROLLER_H