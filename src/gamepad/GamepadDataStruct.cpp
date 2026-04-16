//
// Created by Alexander on 10.04.2026.
//

#include "GamepadDataStruct.h"

#include <fstream>
#include "../Logger.h"
#include "magic_enum/magic_enum.hpp"


void GamepadDataStruct::init() {
    std::ifstream file(PATH);
    if (!file.is_open()) {
        Logger::criticalError("Can not load file under path: " + PATH.filename().string());
        return;
    }
    try {
        nlohmann::json data;
        file >> data;
        readButtonsData(data);
        Logger::debug("All the pins were read successfully");
    }
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "Parsing error: " << e.what() << std::endl;
    }
}

GamepadDataStruct::GamepadDataStruct() {
    init();
}

void GamepadDataStruct::readButtonsData(nlohmann::json::const_reference json) {
    //int buzzerDigital = json[BUZZER_DIGITAL];

}

