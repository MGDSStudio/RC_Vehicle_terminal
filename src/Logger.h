//
// Created by gorod on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_LOGGER_H
#define CMAKESFMLPROJECT_LOGGER_H
#include <iostream>
#include <ostream>
#include <string>

static const std::string DEBUG = "DEBUG: ";
static const std::string ERROR = "ERROR: ";

class Logger {

public:
    static void debug(const std::string &text) {
        const std::string message = std::to_string(getMessageNumber())+' '+DEBUG+text;
        std::cout << message << std::endl;
    }

    static void custom(const std::string &prefix, const std::string &text) {
        const std::string message =  std::to_string(getMessageNumber())+' '+prefix+text;
        std::cout << message << std::endl;
    }


    static void criticalError( const std::string &text) {
        const std::string message =  std::to_string(getMessageNumber())+' '+ERROR+text;
        std::cerr << message << std::endl;
    }
private:
    inline static int messageCounter = 0;
    static int getMessageNumber() {
        const int messageNumber = messageCounter;
        messageCounter++;
        return messageNumber;
    }
};


#endif //CMAKESFMLPROJECT_LOGGER_H