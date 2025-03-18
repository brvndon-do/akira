#pragma once

#include <SDL3/SDL.h>
#include "structs.h"

Entity *init_entity(int x, int y, int w, int h);

void destroy_entity(Entity *entity);