#include <stdio.h>
#include <SDL3/SDL.h>

#include "event_handler.h"

void update_collision_box(Entity *entity) {
    entity->collision_box.x = entity->x_pos;
    entity->collision_box.y = entity->y_pos;
}

bool is_collided(SDL_Rect *source_rect, SDL_Rect *target_rect) {
    return SDL_HasRectIntersection(source_rect, target_rect);
}

void handle_input(SystemManager *manager, SDL_Scancode key_code, bool is_pressed) {
    InputState *input_state = get_system(manager, SYSTEM_INPUT);
    
    if (!input_state) {
        return;
    }

    input_state->keys[key_code] = is_pressed;
}

void update(SystemManager *manager, double delta_time) {
    const float speed = 100.0f;

    GameContext *game_context = get_system(manager, SYSTEM_GAME);
    InputState *input_state = get_system(manager, SYSTEM_INPUT);

    if (!game_context || !input_state) {
        return;
    }

    Entity *player = game_context->player_entity;

    if (input_state->keys[SDL_SCANCODE_UP]) {
        player->y_pos -= speed * delta_time;
    }

    if (input_state->keys[SDL_SCANCODE_DOWN]) {
        player->y_pos += speed * delta_time;
    }

    if (input_state->keys[SDL_SCANCODE_LEFT]) {
        player->x_pos -= speed * delta_time;
    }

    if (input_state->keys[SDL_SCANCODE_RIGHT]) {
        player->x_pos += speed * delta_time;
    }
}

void render(SystemManager *manager, SDL_Renderer *renderer) {
    GameContext *game_context = get_system(manager, SYSTEM_GAME);

    Entity *player = game_context->player_entity;
    Entity *test = game_context->test_entity;

    SDL_FRect player_rect = {
        .x = player->x_pos,
        .y = player->y_pos,
        .w = player->collision_box.w,
        .h = player->collision_box.h
    };

    SDL_FRect test_rect = {
        .x = test->x_pos,
        .y = test->y_pos,
        .w = player->collision_box.w,
        .h = player->collision_box.h
    };

    update_collision_box(player);
    update_collision_box(test);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player_rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1);
    SDL_RenderFillRect(renderer, &test_rect);

    if (is_collided(&player->collision_box, &test->collision_box)) {
        printf("collided\n");
    }
}