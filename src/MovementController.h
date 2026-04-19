
//
// Created by Alexander on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_MOVEMENTCONTROLLER_H
#define CMAKESFMLPROJECT_MOVEMENTCONTROLLER_H


#include "LocalCommandsListener.h"
#include "IUpdateable.h"
#include "gpio/SinglePinActor.h"
#include "gpio/WheelActor.h"
#include "gpio/WheelsSignalsCalculatorDigital.h"
#include "gpio/ReleasePinHardware.h"
#include "gpio/ReleasePinSoftware.h"
#include "gpio/WheelsSignalsCalculatorAnalog.h"

enum class ControlType{
    ANALOG, DIGITAL, NOTHING
};

class MovementController : public IUpdateable, LocalCommandsListener{

public:
    MovementController();
    ~MovementController() override;
    void update(float tpf) override;
    void complete() override;
    void updateMovementAnalog(float get_float_value) const;
    void updateRotationAnalog(float get_float_value) const;
    void onCommandReceived(const LocalCommand& local_command) override;

private:
    WheelActor wheelForwardLeft;
    WheelActor wheelForwardRight;
    WheelActor wheelBackwardLeft;
    WheelActor wheelBackwardRight;
    WheelsSignalsCalculatorDigital* wheelSignalsCalculatorDigital;
    WheelsSignalsCalculatorAnalog* wheelSignalsCalculatorAnalog;
    ControlType actualControl = ControlType::NOTHING;
    inline static const float DEAD_ZONE_MIN = -0.075;   //can be avoided - it was mapped in gamepad controller
    inline static const float DEAD_ZONE_MAX = 0.075; //can be avoided - it was mapped in gamepad controller
    static bool inDeadZone(const float val) {
        return (val>=DEAD_ZONE_MIN && val<=DEAD_ZONE_MAX);
    }

};

#endif //CMAKESFMLPROJECT_MOVEMENTCONTROLLER_H
