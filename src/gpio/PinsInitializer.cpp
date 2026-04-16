//
// Created by gorod on 10.04.2026.
//

#include "PinsInitializer.h"

#include <fstream>
#include <iosfwd>
#include <iostream>
#include "../Logger.h"

#include "magic_enum/magic_enum.hpp"

bool PinsInitializer::initialized = false;

std::pmr::unordered_map<PinActionName, int> * PinsInitializer::getPins() {
    if (!initialized) init();
    return &pins;
}

void PinsInitializer::init() {
    std::ifstream file(PATH);
    if (!file.is_open()) {
        std::cerr << "Can not load file!" << std::endl;
        return;
    }
    try {
        nlohmann::json data;
        file >> data;
        int number;
        constexpr auto pinActionNames = magic_enum::enum_names<PinActionName>();
        for (auto nameView: pinActionNames){           
            std::string name{nameView};
            addInMap(name, &data);
        }
        Logger::debug("All the pins were read successfully");
    } 
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "Parsing error: " << e.what() << std::endl;
    }
    initialized = true;
}

void PinsInitializer::addInMap(const std::string name, nlohmann::json* data){
    auto pinActionEnum = magic_enum::enum_cast<PinActionName>(name);    
    if (pinActionEnum.has_value()){        
        int pinNumber = data->at(name).get<int>();
        pins.emplace(pinActionEnum.value(), pinNumber);
        std::string numberAsString = std::to_string(pinNumber);
        Logger::debug(name + " added data in map for PIN " + numberAsString + "; In map: " + std::to_string(pins.size()));
    }
    else {
        Logger::debug("Wrong data in JSON");
    }
}


