//
// Created by Alexander on 09.04.2026.
//

#include "MovementController.h"

#include "LocalCommandsListenersObserverSingleton.h"
#include "gpio/PinsInitializer.h"

MovementController::MovementController() {
    PinsInitializer pins_initializer;
    std::pmr::unordered_map<PinActionName, int> * map = pins_initializer.getPins();

    auto pinNumberLeftFrontForward = map->at(PinActionName::LEFT_FRONT_WHEEL_FORWARD);
    this->wheelForwardLeft.setPinForward(new ReleasePinSoftware(pinNumberLeftFrontForward));
    this->wheelForwardLeft.setHardwarePinForward(new ReleasePinHardware(pinNumberLeftFrontForward));
    auto pinNumberLeftFrontBackward = map->at(PinActionName::LEFT_FRONT_WHEEL_BACKWARD);
    this->wheelForwardLeft.setPinBackward(new ReleasePinSoftware(pinNumberLeftFrontBackward));
    this->wheelForwardLeft.setHardwarePinBackward(new ReleasePinHardware(pinNumberLeftFrontBackward));

    auto pinNumberRightFrontForward = map->at(PinActionName::RIGHT_FRONT_WHEEL_FORWARD);
    this->wheelForwardRight.setPinForward(new ReleasePinSoftware(pinNumberRightFrontForward));
    this->wheelForwardRight.setHardwarePinForward(new ReleasePinHardware(pinNumberRightFrontForward));
    auto pinNumberRightFrontBackward = map->at(PinActionName::RIGHT_FRONT_WHEEL_BACKWARD);
    this->wheelForwardRight.setPinBackward(new ReleasePinSoftware(pinNumberRightFrontBackward));
    this->wheelForwardRight.setHardwarePinBackward(new ReleasePinHardware(pinNumberRightFrontBackward));


    auto pinNumberLeftRearForward = map->at(PinActionName::LEFT_REAR_WHEEL_FORWARD);
    this->wheelBackwardLeft.setPinForward(new ReleasePinSoftware(pinNumberLeftRearForward));
    this->wheelBackwardLeft.setHardwarePinForward(new ReleasePinHardware(pinNumberLeftRearForward));
    auto pinNumberLeftRearBackward = map->at(PinActionName::LEFT_REAR_WHEEL_BACKWARD);
    this->wheelBackwardLeft.setPinBackward(new ReleasePinSoftware(pinNumberLeftRearBackward));
    this->wheelBackwardLeft.setHardwarePinBackward(new ReleasePinHardware(pinNumberLeftRearBackward));

    const auto pinNumberRightRearForward = map->at(PinActionName::RIGHT_REAR_WHEEL_FORWARD);
    this->wheelBackwardRight.setPinForward(new ReleasePinSoftware(pinNumberRightRearForward));
    this->wheelBackwardRight.setHardwarePinForward(new ReleasePinHardware(pinNumberRightRearForward));
    auto pinNumberRightRearBackward = map->at(PinActionName::RIGHT_REAR_WHEEL_BACKWARD);
    this->wheelBackwardRight.setPinBackward(new ReleasePinSoftware(pinNumberRightRearBackward));
    this->wheelBackwardRight.setHardwarePinBackward(new ReleasePinHardware(pinNumberRightRearBackward));

    //WheelActor* wheelForwardLeft, WheelActor* wheelForwardRight, WheelActor* wheelBackwardLeft, WheelActor* wheelBackwardRight
    this->wheelSignalsCalculator = new WheelsSignalsCalculatorSimple(&wheelForwardLeft, &wheelForwardRight, &wheelBackwardLeft, &wheelBackwardRight);

    LocalCommandsListenersObserverSingleton::getInstance().subscribe(this);



    Logger::debug("Movement controller init successfully");
}

MovementController::~MovementController() {
    delete wheelSignalsCalculator;
}


void MovementController::update(float tpf){
    
}

void MovementController::complete() {
}

void MovementController::applyMovementForward(LocalCommand* localCommand){

}

void MovementController::onCommandReceived(LocalCommand &global_command) {
    if (global_command.getPrefix() == LocalCommandPrefix::MOVEMENT_FORWARD || global_command.getPrefix() == LocalCommandPrefix::MOVEMENT_BACKWARD){
        applyMovementForward(&global_command);
        float value = global_command.getFloatValue();
        if (inDeadZone(value)) {
            wheelSignalsCalculator->stopAll();
            //Logger::debug("Stop movement");
        }
        else if (value < 0){
            //buzzer.enable(true);
            wheelSignalsCalculator->applyMoveForward(value);
            //Logger::debug("Move forward");
        }
        else {
            //buzzer.enable(false);
            wheelSignalsCalculator->applyMoveBackward(value);
           // Logger::debug("Move backward");
        }
    }
    else if (global_command.getPrefix() == LocalCommandPrefix::ROTATION_CW || global_command.getPrefix() == LocalCommandPrefix::ROTATION_CCW) {
        float value = global_command.getFloatValue();
        if (inDeadZone(value)) {
            wheelSignalsCalculator->stopAll();
            //Logger::debug("Stop rotation");
        }
        else if (value > 0){
            //buzzer.enable(true);
            wheelSignalsCalculator->applyRotationCw(value);
            //Logger::debug("Rotate cw");
        }
        else {
            //buzzer.enable(false);
            wheelSignalsCalculator->applyRotationCcw(value);
            //Logger::debug("Rotate ccw");
        }
    }
    else {
        //auto val = global_command.getPrefix();
        //Logger::debug("Wrong prefix for command" );
    }
}

void MovementController::applyRotation(LocalCommand *localCommand) {

}
