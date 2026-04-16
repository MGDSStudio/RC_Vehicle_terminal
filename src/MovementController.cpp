//
// Created by Alexander on 09.04.2026.
//

#include "MovementController.h"

#include "GlobalCommandsListenersObserverSingleton.h"
#include "gpio/PinsInitializer.h"

MovementController::MovementController() {
    PinsInitializer pins_initializer;
    std::pmr::unordered_map<PinActionName, int> * map = pins_initializer.getPins();

    auto pinNumberLeftFrontForward = map->at(PinActionName::LEFT_FRONT_WHEEL_FORWARD);
    this->wheelForwardLeft.setPinForward(new SoftwarePin(pinNumberLeftFrontForward));
    this->wheelForwardLeft.setHardwarePinForward(new PinCommon(pinNumberLeftFrontForward));
    auto pinNumberLeftFrontBackward = map->at(PinActionName::LEFT_FRONT_WHEEL_BACKWARD);
    this->wheelForwardLeft.setPinBackward(new SoftwarePin(pinNumberLeftFrontBackward));
    this->wheelForwardLeft.setHardwarePinBackward(new PinCommon(pinNumberLeftFrontBackward));

    auto pinNumberRightFrontForward = map->at(PinActionName::RIGHT_FRONT_WHEEL_FORWARD);
    this->wheelForwardRight.setPinForward(new SoftwarePin(pinNumberRightFrontForward));
    this->wheelForwardRight.setHardwarePinForward(new PinCommon(pinNumberRightFrontForward));
    auto pinNumberRightFrontBackward = map->at(PinActionName::RIGHT_FRONT_WHEEL_BACKWARD);
    this->wheelForwardRight.setPinBackward(new SoftwarePin(pinNumberRightFrontBackward));
    this->wheelForwardRight.setHardwarePinBackward(new PinCommon(pinNumberRightFrontBackward));


    auto pinNumberLeftRearForward = map->at(PinActionName::LEFT_REAR_WHEEL_FORWARD);
    this->wheelBackwardLeft.setPinForward(new SoftwarePin(pinNumberLeftRearForward));
    this->wheelBackwardLeft.setHardwarePinForward(new PinCommon(pinNumberLeftRearForward));
    auto pinNumberLeftRearBackward = map->at(PinActionName::LEFT_REAR_WHEEL_BACKWARD);
    this->wheelBackwardLeft.setPinBackward(new SoftwarePin(pinNumberLeftRearBackward));
    this->wheelBackwardLeft.setHardwarePinBackward(new PinCommon(pinNumberLeftRearBackward));

    const auto pinNumberRightRearForward = map->at(PinActionName::RIGHT_REAR_WHEEL_FORWARD);
    this->wheelBackwardRight.setPinForward(new SoftwarePin(pinNumberRightRearForward));
    this->wheelBackwardRight.setHardwarePinForward(new PinCommon(pinNumberRightRearForward));
    auto pinNumberRightRearBackward = map->at(PinActionName::RIGHT_REAR_WHEEL_BACKWARD);
    this->wheelBackwardRight.setPinBackward(new SoftwarePin(pinNumberRightRearBackward));
    this->wheelBackwardRight.setHardwarePinBackward(new PinCommon(pinNumberRightRearBackward));

    //WheelActor* wheelForwardLeft, WheelActor* wheelForwardRight, WheelActor* wheelBackwardLeft, WheelActor* wheelBackwardRight
    this->wheelSignalsCalculator = new WheelSignalsCalculator(&wheelForwardLeft, &wheelForwardRight, &wheelBackwardLeft, &wheelBackwardRight);

    GlobalCommandsListenersObserverSingleton::getInstance().subscribe(this);



    Logger::debug("Movement controller init successfully");
}

MovementController::~MovementController() {
    delete wheelSignalsCalculator;
}


void MovementController::update(float tpf){
    
}

void MovementController::complete() {
}

void MovementController::onCommandReceived(GlobalCommand &global_command) {
    //GlobalCommandsListener::onCommandReceived(global_command);
    if (global_command.getPrefix() == GlobalCommandPrefix::MOVEMENT){
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
    else if (global_command.getPrefix() == GlobalCommandPrefix::ROTATION) {
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
