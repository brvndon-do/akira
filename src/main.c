#include <stdio.h>
#include <SDL3/SDL.h>

#include "event_handler.h"
#include "system.h"
#include "app.h"
#include "game.h"
#include "entity.h"
#include "input.h"

#define FPS 60
#define MS_PER_FRAME (1000 / FPS)

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("main: could not initialize SDL: '%s'\n", SDL_GetError());
        SDL_Quit();
    }

    SystemManager manager;
    init_manager(&manager);
    
    // register systems
    register_system(&manager, SYSTEM_APP, (SystemInitFunction)init_app_state, (SystemDestroyFunction)destroy_app_state);
    register_system(&manager, SYSTEM_INPUT, (SystemInitFunction)init_input_state, (SystemDestroyFunction)destroy_input_state);
    register_system(&manager, SYSTEM_GAME, (SystemInitFunction)init_game_context, (SystemDestroyFunction)destroy_game_context);

    init_all_systems(&manager);

    SDL_Renderer *renderer = ((AppState *)get_system(&manager, SYSTEM_APP))->renderer;

    // game loop
    bool is_running = true;
    SDL_Event event;
    uint32_t previous = SDL_GetTicks();
    uint32_t current, frame_time;

    while (is_running) {
        current = SDL_GetTicks();
        double delta_time = (current - previous) / 1000.0;
        previous = current;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    is_running = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    handle_input(&manager, event.key.scancode, true);
                    break;
                case SDL_EVENT_KEY_UP:
                    handle_input(&manager, event.key.scancode, false);
                default:
                    break;
            }
        }

        update(&manager, delta_time);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        render(&manager, renderer);

        SDL_RenderPresent(renderer);

        frame_time = SDL_GetTicks() - current;
        if (frame_time < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - frame_time);
        }
    }

    destroy_manager(&manager);
}