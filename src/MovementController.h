
//
// Created by Alexander on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_MOVEMENTCONTROLLER_H
#define CMAKESFMLPROJECT_MOVEMENTCONTROLLER_H


#include "GlobalCommandsListener.h"
#include "IUpdateable.h"
#include "gpio/SinglePinActor.h"
#include "WheelActor.h"
#include "WheelSignalsCalculator.h"
#include "gpio/SoftwarePin.h"

class MovementController : public IUpdateable, GlobalCommandsListener{

public:
    MovementController();
    ~MovementController();
    void update(float tpf) override;
    void complete() override;
    void onCommandReceived(GlobalCommand& global_command) override;


private:
    WheelActor wheelForwardLeft;
    WheelActor wheelForwardRight;
    WheelActor wheelBackwardLeft;
    WheelActor wheelBackwardRight;
    WheelSignalsCalculator* wheelSignalsCalculator;
    inline static const float DEAD_ZONE_MIN = -0.075;
    inline static const float DEAD_ZONE_MAX = 0.075;

    static bool inDeadZone(const float val) {
        return (val>=DEAD_ZONE_MIN && val<=DEAD_ZONE_MAX);
    }
};


#endif //CMAKESFMLPROJECT_MOVEMENTCONTROLLER_H
