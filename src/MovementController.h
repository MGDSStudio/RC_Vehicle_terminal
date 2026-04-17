
//
// Created by Alexander on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_MOVEMENTCONTROLLER_H
#define CMAKESFMLPROJECT_MOVEMENTCONTROLLER_H


#include "LocalCommandsListener.h"
#include "IUpdateable.h"
#include "gpio/SinglePinActor.h"
#include "gpio/WheelActor.h"
#include "gpio/WheelsSignalsCalculatorSimple.h"
#include "gpio/ReleasePinHardware.h"
#include "gpio/ReleasePinSoftware.h"



class MovementController : public IUpdateable, LocalCommandsListener{

public:
    MovementController();
    ~MovementController() override;
    void update(float tpf) override;
    void complete() override;
    void onCommandReceived(LocalCommand& local_command) override;

private:
    WheelActor wheelForwardLeft;
    WheelActor wheelForwardRight;
    WheelActor wheelBackwardLeft;
    WheelActor wheelBackwardRight;
    WheelsSignalsCalculatorSimple* wheelSignalsCalculator;
    inline static const float DEAD_ZONE_MIN = -0.075;
    inline static const float DEAD_ZONE_MAX = 0.075;
    void applyMovementForward(LocalCommand* localCommand);
    void applyRotation(LocalCommand* localCommand);

    static bool inDeadZone(const float val) {
        return (val>=DEAD_ZONE_MIN && val<=DEAD_ZONE_MAX);
    }
};

#endif //CMAKESFMLPROJECT_MOVEMENTCONTROLLER_H
