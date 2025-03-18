#include "input.h"

InputState *init_input_state() {
    InputState *input_state = SDL_malloc(sizeof(InputState));

    return input_state;
}

void destroy_input_state(InputState *inputState) {
    SDL_free(inputState);
}