#include <stdio.h>

#include "event_handler.h"

void update (double delta_time) {
    printf("hello world from update\n");
}

void render(SDL_Renderer *renderer) {
    printf("hello world from render\n");
}