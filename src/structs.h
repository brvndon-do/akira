#include <SDL3/SDL.h>

typedef struct AppState_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
    void *game_context;
} AppState_t;