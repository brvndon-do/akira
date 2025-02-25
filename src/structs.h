#include <SDL3/SDL.h>

typedef struct Entity_t {
    float x_pos;
    float y_pos;
    SDL_Rect collision_box;
} Entity_t;

typedef struct InputState_t {
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;
} InputState_t;

typedef struct GameContext_t { 
    Entity_t *player_entity;
    Entity_t *test_entity;
} GameContext_t;

typedef struct AppState_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
    InputState_t *input_state;
    GameContext_t *game_context;
} AppState_t;