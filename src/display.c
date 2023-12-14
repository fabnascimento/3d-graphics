//
// Created by ffnas on 12/13/2023.
//

#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

int window_width = 1280;
int window_height = 720;

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

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    // I believe we don't need to loop all pixels in the screen
    // x ~ width, y ~ height

    for(int pixel_y = y; pixel_y < y+height; pixel_y++) {
        for (int pixel_x = x; pixel_x < x+width; pixel_x++) {
            color_buffer[(pixel_y * window_width) + pixel_x] = color;
        }
    }
}

void clear_color_buffer(uint32_t color) {
    for(int i = 0; i < window_height * window_width; i++) {
        color_buffer[i] = color;
    }
}

void render_color_buffer() {
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, window_width * sizeof(uint32_t));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void destroy_window() {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}