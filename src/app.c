#include "app.h"
#include "game.h"

#define APP_NAME "Akira"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

AppState *init_app_state() {
    AppState *app_state = SDL_calloc(1, sizeof(AppState));

    if (!SDL_SetAppMetadata(APP_NAME, "1.0.0", NULL)) {
        SDL_Log("app: could not set metadata: '%s'\n", SDL_GetError());
    }

    if (!SDL_CreateWindowAndRenderer(APP_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, 0, &app_state->window, &app_state->renderer)) {
        SDL_Log("app: could not create window and renderer: '%s'\n", SDL_GetError());
        destroy_app_state(app_state);
        return NULL;
    }

    if (!SDL_SetWindowPosition(app_state->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)) {
        SDL_Log("app: could not set window position: '%s'\n", SDL_GetError());
    }

    return app_state;
}

void destroy_app_state(AppState *app_state) {
    SDL_DestroyWindow(app_state->window);
    SDL_DestroyRenderer(app_state->window);

    SDL_free(app_state);
}