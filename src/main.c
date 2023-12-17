#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

// creating an array of points/vectors
#define n_points 729 // 9 * 9 * 9
vec3_t cube_points[n_points];
vec2_t projected_points[n_points];

vec3_t camera_position = { .x=0, .y=0, .z= -5 };

float fov_factor = 1024;

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

    int point_count = 0;
    // from -1 to 1 (in this 9^3 cube)
    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3_t new_point = { x, y, z };
                cube_points[point_count++] = new_point;
            }
        }
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

vec2_t project (vec3_t point) {
    // naive orthographic
    vec2_t projected_point = { .x=(point.x * fov_factor) / point.z, .y=(point.y * fov_factor) / point.z };
    return projected_point;
}

void update() {
    for (int i = 0; i < n_points; i++) {
        vec3_t point = cube_points[i];
        // move the points away from the camera
        point.z -= camera_position.z;

        vec2_t projected_point = project(point);

        // saves the projected 2D vector in the array of projected vectors
        projected_points[i] = projected_point;
    }
}

void render() {
    // colorbuffer - an array of colors
    // 0x = hex number
    // 0xFFFF0000
    //   A R G B
    // ...
    clear_color_buffer(0xFF000000);

    draw_grid(10);

    // loop all projected points and render them
    for (int i = 0; i < n_points; i++) {
        vec2_t projected_point = projected_points[i];
        draw_rect(
            projected_point.x + (window_width/2),
            projected_point.y + (window_height/2),
            4,
            4,
            0xFFFFAAAA
        );
    }

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
