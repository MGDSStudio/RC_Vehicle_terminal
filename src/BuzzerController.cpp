//
// Created by gorod on 10.04.2026.
//

#include "BuzzerController.h"

#include "GeometrieLibrary.h"


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
    Logger::debug("buzzer pin at: " + std::to_string(buzzerPin) + " init successfully");
    this->buzzer.setPin(new SoftwarePin(buzzerPin));
    this->buzzer.setPinCommon(new PinCommon(buzzerPin));
    LocalCommandsListenersObserverSingleton::getInstance().subscribe(this);
}

void BuzzerController::update(float tpf) {

}

void BuzzerController::onCommandReceived(LocalCommand& global_command){
    if (global_command.getPrefix() == LocalCommandPrefix::NOISE_DIGITAL){
        bool enable = global_command.getBool();
        //float floatVal = global_command.getFloatValue();
        //Logger::debug("Float buzzer value is: " + std::to_string(floatVal));
        if (enable){
            buzzer.enable(true);
            Logger::debug("Buzzer enabled from digital command");
        }
        else {
            buzzer.enable(false);
            Logger::debug("Buzzer disabled from digital command");
        }
    }
    else if (global_command.getPrefix() == LocalCommandPrefix::NOISE_ANALOG) {
        float floatVal = global_command.getFloatValue();
        float mappedFromNullUpToOne = GeometrieLibrary::map(floatVal, Constants::MIN_ANALOG_VALUE, Constants::MAX_ANALOG_VALUE, 0, Constants::MAX_ANALOG_VALUE);
        //Logger::debug("Buzzer enabled from analog command to value: " + std::to_string(mappedFromNullUpToOne) + " from original " + std::to_string(floatVal));

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
[build]    13 |     this->buzzer.setPin(new SoftwarePin(buzzerPin));*/