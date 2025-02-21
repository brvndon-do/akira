#include <SDL3/SDL.h>

typedef struct InputState_t {
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;
} InputState_t;

typedef struct GameContext_t { 
    float x_pos;
    float y_pos;
} GameContext_t;

typedef struct AppState_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
    InputState_t *input_state;
    GameContext_t *game_context;
} AppState_t;