#include <SDL3/SDL.h>

#include "structs.h"

void handle_input(SystemManager *manager, SDL_Scancode key_code, bool is_pressed);
void update(SystemManager *manager, double delta_time);
void render(SystemManager *manager, SDL_Renderer *renderer);