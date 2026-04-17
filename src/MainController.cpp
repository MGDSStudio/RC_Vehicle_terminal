//
// Created by gorod on 16.04.2026.
//

#include "MainController.h"

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
    delete completeFlagApplicationLevel;
    keepRunning = false;
    if (consoleThread.joinable()) {
        // Since std::cin is blocking, detach is often safer for CLI apps
        // to prevent the app from hanging on exit
        consoleThread.detach();
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
