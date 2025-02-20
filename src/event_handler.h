#include <SDL3/SDL.h>

#include "structs.h"

void update(double delta_time, void *game_context);
void render(SDL_Renderer *renderer);
void cleanup(AppState_t *app_state);