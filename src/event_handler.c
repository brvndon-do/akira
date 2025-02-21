#include <stdio.h>
#include <SDL3/SDL.h>

#include "event_handler.h"

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
    Entity_t *player = (Entity_t *)game_context->player_entity;

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
    Entity_t *player = (Entity_t *)game_context->player_entity;

    SDL_FRect rect = { player->x_pos, player->y_pos, 200, 200 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void cleanup(AppState_t *app_state) {
    SDL_DestroyWindow(app_state->window);
    SDL_DestroyRenderer(app_state->renderer);

    SDL_free(app_state->input_state);
    SDL_free(app_state->game_context->player_entity);
    SDL_free(app_state->game_context);
    SDL_free(app_state);
}