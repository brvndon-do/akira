#include <stdio.h>
#include <SDL3/SDL.h>

#include "event_handler.h"

void update_collision_box(Entity_t *entity) {
    entity->collision_box.x = entity->x_pos;
    entity->collision_box.y = entity->y_pos;
}

bool is_collided(SDL_Rect *source_rect, SDL_Rect *target_rect) {
    return SDL_HasRectIntersection(source_rect, target_rect);
}

void handle_input(SDL_Scancode key_code, bool is_pressed, InputState_t *input_state) {
    switch (key_code) {
        case SDL_SCANCODE_UP:
            input_state->move_up = is_pressed;
            break;
        case SDL_SCANCODE_DOWN:
            input_state->move_down = is_pressed;
            break;
        case SDL_SCANCODE_LEFT:
            input_state->move_left = is_pressed;
            break;
        case SDL_SCANCODE_RIGHT:
            input_state->move_right = is_pressed;
            break;
        default:
            break;
    }
}

void update (double delta_time, InputState_t *input_state, GameContext_t *game_context) {
    const float speed = 100.0f;
    Entity_t *player = game_context->player_entity;

    if (input_state->move_up) {
        player->y_pos -= speed * delta_time;
    }

    if (input_state->move_down) {
        player->y_pos += speed * delta_time;
    }

    if (input_state->move_left) {
        player->x_pos -= speed * delta_time;
    }

    if (input_state->move_right) {
        player->x_pos += speed * delta_time;
    }
}

void render(SDL_Renderer *renderer, GameContext_t *game_context) {
    Entity_t *player = game_context->player_entity;
    Entity_t *test = game_context->test_entity;

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

void cleanup(AppState_t *app_state) {
    SDL_DestroyWindow(app_state->window);
    SDL_DestroyRenderer(app_state->renderer);

    SDL_free(app_state->input_state);
    SDL_free(app_state->game_context->player_entity);
    SDL_free(app_state->game_context->test_entity);
    SDL_free(app_state->game_context);
    SDL_free(app_state);
}