#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"

triangle_t triangles_to_render[MESH_FACE_AMOUNT];

vec3_t camera_position = { .x=0, .y=0, .z= -5 };
vec3_t cube_rotation = {0, 0, 0};

float fov_factor = 1024;

bool is_running = false;
Uint32 previous_frame_time = 0;

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

vec2_t project (vec3_t point) {
    // naive orthographic
    vec2_t projected_point = { .x=(point.x * fov_factor) / point.z, .y=(point.y * fov_factor) / point.z };
    return projected_point;
}

void update() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    previous_frame_time = SDL_GetTicks();

    cube_rotation.y += 0.01;
    cube_rotation.z += 0.01;
    cube_rotation.x += 0.01;

    // loop the faces first?
    for (int i = 0; i < MESH_FACE_AMOUNT; i++) {
        face_t current_face = mesh_faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh_vertices[current_face.a - 1];
        face_vertices[1] = mesh_vertices[current_face.b - 1];
        face_vertices[2] = mesh_vertices[current_face.c - 1];

        triangle_t projected_triangle;

        for (int j = 0; j < 3; j++) {
            vec3_t current_vertex = face_vertices[j];

            current_vertex = vec3_rotate_x(current_vertex, cube_rotation.x);
            current_vertex = vec3_rotate_y(current_vertex, cube_rotation.y);
            current_vertex = vec3_rotate_z(current_vertex, cube_rotation.z);

            // move points away from the camera
            current_vertex.z -= camera_position.z;

            vec2_t projected_point = project(current_vertex);

            // scale and translate to center
            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }

        triangles_to_render[i] = projected_triangle;
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

    for(int i = 0; i < MESH_FACE_AMOUNT; i++) {
        const triangle_t current_triangle = triangles_to_render[i];
        for (int point = 0; point < 3; point++) {
            draw_rect(current_triangle.points[point].x,
                      current_triangle.points[point].y,
                      4,
                      4,
                      0xFFFF5050
            );
        }
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
