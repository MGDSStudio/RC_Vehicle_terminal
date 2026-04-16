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
    Logger::debug("App completed");
}


/*
 *
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    // 1. Инициализация подсистем видео и геймпада
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        SDL_Log("Ошибка инициализации: %s", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 Gamepad Example", 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    SDL_Gamepad* gamepad = nullptr;

    bool running = true;
    SDL_Event event;

    // 2. Главный цикл программы
    while (running) {
        // 3. Обработка очереди событий
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                // Событие подключения геймпада
                case SDL_EVENT_GAMEPAD_ADDED:
                    if (!gamepad) {
                        gamepad = SDL_OpenGamepad(event.gdevice.which);
                        if (gamepad) {
                            std::cout << "Геймпад подключен: " << SDL_GetGamepadName(gamepad) << std::endl;
                        }
                    }
                    break;

                // Событие отключения
                case SDL_EVENT_GAMEPAD_REMOVED:
                    if (gamepad && event.gdevice.which == SDL_GetGamepadID(gamepad)) {
                        std::cout << "Геймпад отключен." << std::endl;
                        SDL_CloseGamepad(gamepad);
                        gamepad = nullptr;
                    }
                    break;

                // Нажатие кнопки
                case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                    std::cout << "Нажата кнопка: " << (int)event.gbutton.button << std::endl;
                    if (event.gbutton.button == SDL_GAMEPAD_BUTTON_SOUTH) { // Обычно кнопка 'A' или 'Cross'
                        std::cout << "Нажата основная кнопка действия!" << std::endl;
                    }
                    break;

                // Движение стиков (осей)
                case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                    // Значения осей в SDL3: от -32768 до 32767
                    if (SDL_abs(event.gaxis.value) > 8000) { // Мертвая зона
                        std::cout << "Ось " << (int)event.gaxis.axis << " значение: " << event.gaxis.value << std::endl;
                    }
                    break;
            }
        }

        // Рендеринг (здесь просто очистка экрана)
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // 4. Очистка ресурсов
    if (gamepad) SDL_CloseGamepad(gamepad);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
}


 **/