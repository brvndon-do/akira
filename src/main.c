#include <stdio.h>
#include <SDL3/SDL.h>
#include <stdbool.h>

#include "event_handler.h"

#define APP_NAME "Akira"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("main: could not initialize SDL: '%s'\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_SetAppMetadata(APP_NAME, "1.0.0", NULL)) {
        SDL_Log("main: could not set metadata: '%s'\n", SDL_GetError());
    }

    AppState_t *app_state = SDL_calloc(1, sizeof(AppState_t));

    if (!SDL_CreateWindowAndRenderer(APP_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, 0, &app_state->window, &app_state->renderer)) {
        SDL_Log("main: could not create window and renderer: '%s'\n", SDL_GetError());
        SDL_Quit();
    }

    if (!SDL_SetWindowPosition(app_state->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)) {
        SDL_Log("main: could not set window position: '%s'\n", SDL_GetError());
        cleanup(app_state);
        SDL_Quit();
    }

    bool is_running = true;
    SDL_Event event;

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            }
        }

        SDL_SetRenderDrawColor(app_state->renderer, 0, 0, 0, 255);
        SDL_RenderClear(app_state->renderer);
        
        render(app_state->renderer);

        SDL_RenderPresent(app_state->renderer);
    }

    cleanup(app_state);
}