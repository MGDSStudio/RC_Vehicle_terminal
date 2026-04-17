//
// Created by gorod on 16.04.2026.
//

#include "MainController.h"

#include "LocalCommandsListenersObserverSingleton.h"
#include "Logger.h"

MainController::MainController()
{
    //if (!SDL_Init(SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK)) {
    if (!SDL_Init(SDL_INIT_GAMEPAD)) {
        SDL_Log("Ошибка инициализации SDL: %s", SDL_GetError());
        //*this->completeFlagApplicationLevel = true;
    }
    std::cout << "Поиск геймпадов... Нажмите Ctrl+C для выхода." << std::endl;
    gamepadController.attachCompletionFlagData(&completeFlagInputLevel);
    completionController.attachCompletionFlagData(&completeFlagInputLevel);
    consoleThread = std::thread(&MainController::inputHandler, this);
}

MainController::~MainController()
{
    keepRunning = false;
    if (consoleThread.joinable()) {
        consoleThread.detach();
        Logger::debug("Console thread was completed successfully");
    }
}

void MainController::update(float tpf)
{

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                close();
            }
            else
            {
               gamepadController.attachCommand(&event);
            }
        }
        gamepadController.update(1);
        buzzerController.update(1);
        movementController.update(1);
        if (this->completeFlagInputLevel == true)
        {
            close();
        }
        SDL_Delay(30);
}


void MainController::complete()
{
    gamepadController.complete();
    buzzerController.complete();
    movementController.complete();
    completionController.complete();
    LocalCommandsListenersObserverSingleton::getInstance().clear();
    PinsInitializer pins_initializer;
    pins_initializer.complete();
    SDL_Quit();
}

void MainController::inputHandler() {
    std::string command;
    while (keepRunning) {
        if (std::cin >> command) {
            if (command == "CLOSE" || command == "EXIT" || command == "QUIT" || command == "STOP" || command == "close" || command == "exit" || command == "quit" || command == "stop") {
                keepRunning = false;
                SDL_Event quitEvent;
                quitEvent.type = SDL_EVENT_QUIT;
                SDL_PushEvent(&quitEvent);
            }
        }
    }
}
