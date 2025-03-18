#pragma once

#include <SDL3/SDL.h>

#include "system.h"

typedef struct Entity_t {
    float x_pos;
    float y_pos;
    SDL_Rect collision_box;
} Entity;

typedef struct InputState_t {
    bool keys[SDL_SCANCODE_COUNT];
} InputState;

typedef struct GameContext_t { 
    Entity *player_entity;
    Entity *test_entity;
} GameContext;

typedef struct AppState_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
} AppState;