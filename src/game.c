#include "game.h"
#include "entity.h"

GameContext *init_game_context() {
    GameContext *game_context = SDL_calloc(1, sizeof(GameContext));

    game_context->player_entity = create_entity(0, 0, 50, 50);
    game_context->test_entity = create_entity(100, 100, 50, 50);

    return game_context;
}

void destroy_game_context(GameContext *game_context) {
    SDL_free(game_context);
}