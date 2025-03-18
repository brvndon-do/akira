#include "entity.h"

Entity *init_entity(int x, int y, int w, int h) {
    Entity *entity = SDL_calloc(1, sizeof(Entity));

    entity->x_pos = x;
    entity->y_pos = y;

    entity->collision_box = (SDL_Rect){
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };

    return entity;
}

void destroy_entity(Entity *entity) {
    SDL_free(entity);
}