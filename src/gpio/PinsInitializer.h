//
// Created by gorod on 10.04.2026.
//

#ifndef CMAKESFMLPROJECT_PINSCREATOR_H
#define CMAKESFMLPROJECT_PINSCREATOR_H
#include <unordered_map>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "PinActionName.h"
#include "../Constants.h"
#ifdef IS_RPI
    #include <pigpio.h>
#endif

class PinsInitializer {

public:
    std::pmr::unordered_map<PinActionName, int>* getPins();

    void complete() {
    #ifdef IS_RPI
            gpioTerminate();
    #endif
    }

private:
    void init();
    void addInMap(std::string name, nlohmann::json* data);

    const std::filesystem::path PATH = Constants::PATH_TO_DATA / "gpio.json";
    inline static std::pmr::unordered_map<PinActionName, int> pins;
    static bool initialized;
};


#endif //CMAKESFMLPROJECT_PINSCREATOR_H