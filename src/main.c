#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"

bool is_running = false;

void setup(void) {
    color_buffer = (uint32_t*) malloc(
        sizeof(uint32_t) * window_width * window_height
    );

    if (!color_buffer) {
        printf("Color buffer couldn't be initialized");
    }

    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    if (!color_buffer_texture) {
        printf("Color buffer texture couldn't be initialized\n");
    }
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        // when the window is closed this event gets called
        case SDL_QUIT:
            is_running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }
            break;
    }
}

void update() {}

void render() {
    SDL_SetRenderDrawColor(renderer, 255, 150, 150, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    // colorbuffer - an array of colors
    // 0x = hex number
    // 0xFFFF0000
    //   A R G B
    // ...
    clear_color_buffer(0xFF000000);
    draw_rect(10, 10, 300, 100, 0xFF4154FF);
    draw_grid(10);
    render_color_buffer();

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) {
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
