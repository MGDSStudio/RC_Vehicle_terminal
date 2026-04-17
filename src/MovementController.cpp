//
// Created by Alexander on 09.04.2026.
//

#include "MovementController.h"

#include <SDL3/SDL_stdinc.h>

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
    this->wheelSignalsCalculatorDigital = new WheelsSignalsCalculatorDigital(&wheelForwardLeft, &wheelForwardRight, &wheelBackwardLeft, &wheelBackwardRight);
    this->wheelSignalsCalculatorAnalog = new WheelsSignalsCalculatorAnalog(&wheelForwardLeft, &wheelForwardRight, &wheelBackwardLeft, &wheelBackwardRight);
    LocalCommandsListenersObserverSingleton::getInstance().subscribe(this);
    Logger::debug("Movement controller init successfully");
}

MovementController::~MovementController() {
    delete wheelSignalsCalculatorDigital;
    delete wheelSignalsCalculatorAnalog;
    wheelSignalsCalculatorAnalog = nullptr;
    wheelSignalsCalculatorDigital = nullptr;
}


void MovementController::complete() {
    LocalCommandsListenersObserverSingleton::getInstance().unsubscribe(this);
}

void MovementController::updateMovementAnalog(float value) const
{
    wheelSignalsCalculatorAnalog->
}

void MovementController::updateRotationAnalog(float value) const
{
    if (value<=0) wheelSignalsCalculatorDigital->applyRotationCcw(-1*value);
    else wheelSignalsCalculatorDigital->applyRotationCw((value));
}


void MovementController::onCommandReceived(const LocalCommand &local_command) {
    auto prefix = local_command.getPrefix();
    if (prefix == LocalCommandPrefix::PREFIX_MOVEMENT_ANALOG)
    {
        updateMovementAnalog(local_command.getFloatValue());
    }
    else if (prefix == LocalCommandPrefix::PREFIX_ROTATION_ANALOG)
    {
        updateRotationAnalog(local_command.getFloatValue());
    }
    else if (prefix == LocalCommandPrefix::PREFIX_MOVEMENT_FORWARD || prefix == LocalCommandPrefix::PREFIX_MOVEMENT_BACKWARD){
        bool pressed = local_command.getBool();
        if (!pressed) wheelSignalsCalculatorDigital->stopAll();
        if (prefix == LocalCommandPrefix::PREFIX_MOVEMENT_FORWARD) wheelSignalsCalculatorDigital->applyMoveForward();
        else wheelSignalsCalculatorDigital->applyMoveBackward();
    }
    else if (prefix == LocalCommandPrefix::PREFIX_ROTATION_CW || prefix == LocalCommandPrefix::PREFIX_ROTATION_CCW) {
        bool pressed = local_command.getBool();
        if (!pressed) wheelSignalsCalculatorDigital->stopAll();
        if (prefix == LocalCommandPrefix::PREFIX_ROTATION_CW) wheelSignalsCalculatorDigital->applyRotationCw();
        else wheelSignalsCalculatorDigital->applyRotationCcw();
    }
    else {
        //auto val = global_command.getPrefix();
        //Logger::debug("Wrong prefix for command" );
    }
}



/*
void MovementController::onCommandReceived(const LocalCommand &local_command) {
    if (local_command.getPrefix() == LocalCommandPrefix::MOVEMENT_FORWARD || local_command.getPrefix() == LocalCommandPrefix::MOVEMENT_BACKWARD){
        float valueFromMinusOneToOne = local_command.getFloatValue();
        if (inDeadZone(valueFromMinusOneToOne)) {
            wheelSignalsCalculator->stopAll();
        }
        else if (valueFromMinusOneToOne > 0){
            wheelSignalsCalculator->applyMoveForward(valueFromMinusOneToOne);
        }
        else {
            wheelSignalsCalculator->applyMoveBackward(valueFromMinusOneToOne);
        }
    }
    else if (local_command.getPrefix() == LocalCommandPrefix::ROTATION_CW || local_command.getPrefix() == LocalCommandPrefix::ROTATION_CCW) {
        float value = local_command.getFloatValue();
        if (inDeadZone(value)) {
            wheelSignalsCalculator->stopAll();
        }
        else if (value > 0){
            wheelSignalsCalculator->applyRotationCw(value);
        }
        else {
            wheelSignalsCalculator->applyRotationCcw(value);
        }
    }
    else {
        //auto val = global_command.getPrefix();
        //Logger::debug("Wrong prefix for command" );
    }
}
*/