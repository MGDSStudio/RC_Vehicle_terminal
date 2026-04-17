//
// Created by gorod on 14.04.2026.
//

#ifndef CMAKESFMLPROJECT_STICKCONTROLLER_H
#define CMAKESFMLPROJECT_STICKCONTROLLER_H
#include "TouchPlace.h"


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


private:
    static constexpr float DEAD_ZONE_ANGLE = 25;
    TouchPlace touch_place {1,25};
    bool inDeadZone = true;
};


#endif //CMAKESFMLPROJECT_STICKCONTROLLER_H