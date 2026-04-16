
//
// Created by Alexander on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_PREFERENCESLOADER_H
#define CMAKESFMLPROJECT_PREFERENCESLOADER_H
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
using json = nlohmann::json;

class PreferencesLoader {

public:
    void load();
};


#endif //CMAKESFMLPROJECT_PREFERENCESLOADER_H
