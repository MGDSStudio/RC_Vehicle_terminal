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
}

MainController::~MainController()
{
    delete completeFlagApplicationLevel;
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
        if (this->completeFlagInputLevel == true)
        {
            close();
        }
        SDL_Delay(10);
}


void MainController::complete()
{
    gamepadController.complete();
    SDL_Quit();
}
