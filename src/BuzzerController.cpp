//
// Created by gorod on 10.04.2026.
//

#include "BuzzerController.h"

#include "libs/GeometrieLibrary.h"
#include "LocalCommandsListenersObserverSingleton.h"
#include "gpio/ReleasePinHardware.h"
#include "gpio/ReleasePinSoftware.h"


BuzzerController::BuzzerController(){
    init();
}

BuzzerController::~BuzzerController(){
    this->buzzer.complete();
}

void BuzzerController::init() {
    Logger::debug("Start to init buzzer-controller");
    PinsInitializer pins_initializer;
    std::pmr::unordered_map<PinActionName, int> *map = pins_initializer.getPins();
    auto buzzerPin = map->at(PinActionName::BUZZER);

    bool enableSoftwarePin = true;
    std::string enabled = "disabled";
    #ifdef IS_RPI
        enableSoftwarePin = false;
        enabled = "enabled";
    #endif
    Logger::debug("buzzer pin at: " + std::to_string(buzzerPin) + " init successfully. Hardware enabled: " + enabled);
    this->buzzer.setHardwarePin(new ReleasePinHardware(buzzerPin));
    if (!enableSoftwarePin) buzzerPin = -1;
    this->buzzer.setSoftwarePin(new ReleasePinSoftware(buzzerPin));
    LocalCommandsListenersObserverSingleton::getInstance().subscribe(this);
}

void BuzzerController::update(float tpf) {

}

void BuzzerController::onCommandReceived(const LocalCommand& global_command){
    if (global_command.getPrefix() == LocalCommandPrefix::PREFIX_NOISE_DIGITAL){
        if (bool enable = global_command.getBool()){
            buzzer.enable(true);
            Logger::debug("Buzzer enabled from digital command");
        }
        else {
            buzzer.enable(false);
            Logger::debug("Buzzer disabled from digital command");
        }
    }
    else if (global_command.getPrefix() == LocalCommandPrefix::PREFIX_NOISE_ANALOG) {
        float floatVal = global_command.getFloatValue();
        float mappedFromNullUpToOne = GeometrieLibrary::map(floatVal, Constants::MIN_ANALOG_VALUE, Constants::MAX_ANALOG_VALUE, 0, Constants::MAX_ANALOG_VALUE);
        if (mappedFromNullUpToOne<=DEAD_ZONE_VALUE) {
            buzzer.enable(false);
            return;
        }
        buzzer.setValue(mappedFromNullUpToOne);
        Logger::debug("Buzzer enabled from analog command to value: " + std::to_string(mappedFromNullUpToOne) + " from original " + std::to_string(floatVal));
    }
}

void BuzzerController::complete(){
    buzzer.complete();
    LocalCommandsListenersObserverSingleton::getInstance().unsubscribe(this);
}

/*
failed with

[build] /home/mgdsstudio/Embedded/Programming/RC_Vehicle/RC_Vehicle/src/BuzzerController.cpp: In member function ‘void BuzzerController::init()’:
[build] /home/mgdsstudio/Embedded/Programming/RC_Vehicle/RC_Vehicle/src/BuzzerController.cpp:13:29: error: expected type-specifier before ‘SoftwarePin’
[build]    13 |     this->buzzer.setSoftwarePin(new SoftwarePin(buzzerPin));*/