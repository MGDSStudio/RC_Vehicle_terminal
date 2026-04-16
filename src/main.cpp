#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h> // Essential for cross-platform entry point

int main(int argc, char* argv[]) {
    // 1. Initialize SDL Video
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // 2. Create a window and a renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("SDL3 Hello World", 800, 600, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool keep_running = true;
    SDL_Event event;

    // 3. Main Loop
    while (keep_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                keep_running = false;
            }
        }

        // 4. Rendering (Dark Blue background)
        SDL_SetRenderDrawColor(renderer, 20, 40, 100, 255);
        SDL_RenderClear(renderer);

        // Present the backbuffer
        SDL_RenderPresent(renderer);
    }

    // 5. Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
