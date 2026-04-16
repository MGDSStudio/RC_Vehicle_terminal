#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include  "Logger.h"
#include "MainController.h"


void dispose();

MainController main_controller;
bool exitCommandReceived = false;

int main(int argc, char* argv[]) {
    main_controller.attachCompletionFlagData(&exitCommandReceived);
    while (!exitCommandReceived)
    {
        main_controller.update(1);
    }
    dispose();
    return 0;
}

void dispose()
{
    main_controller.complete();
}


/*
 *int main(int argc, char* argv[]) {
        #ifdef _WIN32
            SetConsoleOutputCP(CP_UTF8);
            SetConsoleCP(CP_UTF8);
        #endif
    // 1. Инициализируем только подсистемы ввода


    Logger::debug("Launched");
    if (!SDL_Init(SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK)) {
        SDL_Log("Ошибка инициализации SDL: %s", SDL_GetError());
        return 1;
    }

    std::cout << "Поиск геймпадов... Нажмите Ctrl+C для выхода." << std::endl;

    bool running = true;
    SDL_Event event;
    SDL_Gamepad* gamepad = nullptr;

    while (running) {
        // 2. Опрашиваем события (обязательно для работы геймпада)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_GAMEPAD_ADDED) {
                if (!gamepad) {
                    gamepad = SDL_OpenGamepad(event.gdevice.which);
                    if (gamepad) {
                        std::cout << "Геймпад подключен: " << SDL_GetGamepadName(gamepad) << std::endl;
                    }
                }
            }
            if (event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
                std::cout << "Нажата кнопка: " << (int)event.gbutton.button << std::endl;
            }
            if (event.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
                // Выводим только если отклонение значительное (мертвая зона)
                if (abs(event.gaxis.value) > 8000) {
                    std::cout << "Ось " << (int)event.gaxis.axis << " значение: " << event.gaxis.value << std::endl;
                }
            }
            if (event.type == SDL_EVENT_GAMEPAD_REMOVED) {
                std::cout << "Геймпад отключен." << std::endl;
                SDL_CloseGamepad(gamepad);
                gamepad = nullptr;
            }
        }
        // Небольшая задержка, чтобы не нагружать процессор (особенно важно для RPi Zero)
        SDL_Delay(10);
    }

    if (gamepad) SDL_CloseGamepad(gamepad);
    dispose();
    SDL_Quit();
    return 0;
}*/