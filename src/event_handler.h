#include <SDL3/SDL.h>

#include "structs.h"

void handle_input(SDL_Scancode key_code, void *game_context);
void update(double delta_time, void *game_context);
void render(SDL_Renderer *renderer);
void cleanup(AppState_t *app_state);