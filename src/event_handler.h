#include <SDL3/SDL.h>

#include "structs.h"

void handle_input(SDL_Scancode key_code, bool is_pressed, InputState_t *input_state);
void update(double delta_time, InputState_t *input_state, GameContext_t *game_context);
void render(SDL_Renderer *renderer, GameContext_t *game_context);
void cleanup(AppState_t *app_state);