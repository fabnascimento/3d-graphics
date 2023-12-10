#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool is_running = false;

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL.\n");
        return false;
    }

    window = SDL_CreateWindow(
        "Janela",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024,
        720,
        SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        printf("Failed to initialize window\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        printf("Failed to initialize renderer\n");
        return false;
    }

    return true;
}

void setup(void) {}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        // when the window is closed this event gets called
        case SDL_QUIT:
            is_running=false;
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

    return 0;
}
