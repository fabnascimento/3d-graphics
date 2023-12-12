#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

int window_width = 1280;
int window_height = 720;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;
bool is_running = false;

uint32_t* color_buffer = NULL;

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL.\n");
        return false;
    }

    // use SDL to query what is the fullscreen max. width and height
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    if (!display_mode.w) {
        printf("Display mode couldn't be retrieved\n");
    }

    window_width = display_mode.w;
    window_height = display_mode.h;

    window = SDL_CreateWindow(
        "Janela",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
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

    // this will actually use fullscreen
    // this allows us to use a lower resolution for the window while maintaining it as fullscreen mode
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void draw_grid(int multiple) {
    for(int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            int pixel_index = (window_width * y) + x;
            if (x % multiple == 0 || y % multiple == 0) {
                color_buffer[pixel_index] = 0xFF555555;
            }
        }
    }
}

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

void clear_color_buffer(uint32_t color) {
    for(int i = 0; i < window_height * window_width; i++) {
        color_buffer[i] = color;
    }
}


void render_color_buffer() {
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, window_width * sizeof(uint32_t));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void render() {
    SDL_SetRenderDrawColor(renderer, 255, 150, 150, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    // colorbuffer - an array of colors
    // 0x = hex number
    // 0xFFFF0000
    //   A R G B
    // ...
    clear_color_buffer(0xFF000000);
    draw_grid(10);
    render_color_buffer();

    SDL_RenderPresent(renderer);
}


void destroy_window() {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
