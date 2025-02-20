#include <stdio.h>
#include <SDL3/SDL.h>

#include "event_handler.h"

void handle_input(SDL_Scancode key_code, void *game_context) {
    GameContext_t *context = (GameContext_t *)game_context;

    switch (key_code) {
        case SDL_SCANCODE_UP:
            context->y_pos += 1;
            break;
        case SDL_SCANCODE_DOWN:
            context->y_pos -= 1;
            break;
        case SDL_SCANCODE_RIGHT:
            context->x_pos += 1;
            break;
        case SDL_SCANCODE_LEFT:
            context->x_pos -= 1;
            break;
        default:
            break;
    }
}

void update (double delta_time, void *game_context) {
    GameContext_t *context = (GameContext_t *)game_context;

    printf("(%f, %f)\n", context->x_pos, context->y_pos);
}

void render(SDL_Renderer *renderer) {
    SDL_FRect rect = { 100, 100, 200, 200 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void cleanup(AppState_t *app_state) {
    SDL_DestroyWindow(app_state->window);
    SDL_DestroyRenderer(app_state->renderer);

    SDL_free(app_state->game_context);
    SDL_free(app_state);
}