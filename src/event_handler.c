#include <stdio.h>
#include <SDL3/SDL.h>

#include "event_handler.h"

void update (double delta_time, void *game_context) {
    printf("hello world from update\n");
}

void render(SDL_Renderer *renderer) {
    SDL_FRect rect = { 100, 100, 200, 200 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void cleanup(AppState_t *app_state) {
    SDL_DestroyWindow(app_state->window);
    SDL_DestroyRenderer(app_state->renderer);
    SDL_free(app_state);
}