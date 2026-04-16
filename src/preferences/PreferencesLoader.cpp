//
// Created by Alexander on 09.04.2026.
//


#include "PreferencesLoader.h"


void PreferencesLoader::load() {
    std::ifstream file("data/pref.json");
    if (!file.is_open()) {
        std::cerr << "Can not load file!" << std::endl;
        return;
    }

    try {
        json data;
        file >> data;
        std::string name = data["name"];
        int version = data["version"];
        std::cout << "Name: " << name << ", Version: " << version << std::endl;

    } catch (json::parse_error& e) {
        std::cerr << "Parsing error: " << e.what() << std::endl;
    }
}


