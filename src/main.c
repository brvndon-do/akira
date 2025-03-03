#include <stdio.h>
#include <SDL3/SDL.h>

#include "event_handler.h"

#define APP_NAME "Akira"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60
#define MS_PER_FRAME (1000 / FPS)

void init_entity(Entity_t *entity, int x, int y, int w, int h) {
    entity->x_pos = x;
    entity->y_pos = y;

    entity->collision_box = (SDL_Rect){
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };
}

AppState_t *initialize_app_state() {
    AppState_t *app_state = SDL_calloc(1, sizeof(AppState_t));

    InputState_t *input_state = SDL_calloc(1, sizeof(InputState_t));
    app_state->input_state = input_state;

    GameContext_t *game_context = SDL_calloc(1, sizeof(GameContext_t));
    app_state->game_context = game_context;

    Entity_t *player_entity = SDL_calloc(1, sizeof(Entity_t));
    init_entity(player_entity, 0, 0, 50, 50);
    app_state->game_context->player_entity = player_entity;

    Entity_t *test_entity = SDL_calloc(1, sizeof(Entity_t));
    init_entity(test_entity, 100, 100, 50, 50);
    app_state->game_context->test_entity = test_entity;

    return app_state;
}

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("main: could not initialize SDL: '%s'\n", SDL_GetError());
        SDL_Quit();
    }

    if (!SDL_SetAppMetadata(APP_NAME, "1.0.0", NULL)) {
        SDL_Log("main: could not set metadata: '%s'\n", SDL_GetError());
    }

    AppState_t *app_state = initialize_app_state();

    if (!SDL_CreateWindowAndRenderer(APP_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, 0, &app_state->window, &app_state->renderer)) {
        SDL_Log("main: could not create window and renderer: '%s'\n", SDL_GetError());
        cleanup(app_state);
        SDL_Quit();
    }

    if (!SDL_SetWindowPosition(app_state->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)) {
        SDL_Log("main: could not set window position: '%s'\n", SDL_GetError());
    }

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
                    handle_input(event.key.scancode, true, app_state->input_state);
                    break;
                case SDL_EVENT_KEY_UP:
                    handle_input(event.key.scancode, false, app_state->input_state);
                default:
                    break;
            }
        }

        update(delta_time, app_state->input_state, app_state->game_context);

        SDL_SetRenderDrawColor(app_state->renderer, 0, 0, 0, 255);
        SDL_RenderClear(app_state->renderer);
        
        render(app_state->renderer, app_state->game_context);

        SDL_RenderPresent(app_state->renderer);

        frame_time = SDL_GetTicks() - current;
        if (frame_time < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - frame_time);
        }
    }

    cleanup(app_state);
}