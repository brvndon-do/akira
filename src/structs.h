#include <SDL3/SDL.h>

typedef struct AppState_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
    void *game_context;
} AppState_t;

typedef struct GameContext_t { 
    float x_pos;
    float y_pos;
} GameContext_t;