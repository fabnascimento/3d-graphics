#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "dynamic_array.h"

triangle_t* triangles_to_render = NULL;

vec3_t camera_position = { 0, 0, 0 };

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

    ARRAY_INIT(triangle_t, triangles_to_render);

    // loads a hard-coded cube into the global mesh data structure
    // load_cube_mesh_data();
    const bool loaded_successfully = load_obj_file("../assets/suzanne_triangulated.obj");
    if (!loaded_successfully) {
        printf("Failed to load example\n");
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
    const vec2_t projected_point = { .x=(point.x * fov_factor) / point.z, .y=(point.y * fov_factor) / point.z };
    return projected_point;
}

void update(void) {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    previous_frame_time = SDL_GetTicks();

    triangles_to_render = NULL;
    ARRAY_INIT(triangle_t, triangles_to_render);

    mesh.rotation.x += 0.01;

    // loop the faces first?
    const int mesh_amount = ARRAY_SIZE(mesh.faces);
    for (int i = 0; i < mesh_amount; i++) {
        face_t current_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[current_face.a - 1];
        face_vertices[1] = mesh.vertices[current_face.b - 1];
        face_vertices[2] = mesh.vertices[current_face.c - 1];

        triangle_t projected_triangle;

        vec3_t transformed_vertices[3];

        // transforms the points
        for (int j = 0; j < 3; j++) {
            vec3_t current_vertex = face_vertices[j];

            current_vertex = vec3_rotate_x(current_vertex, mesh.rotation.x);
            current_vertex = vec3_rotate_y(current_vertex, mesh.rotation.y);
            current_vertex = vec3_rotate_z(current_vertex, mesh.rotation.z);

            // move points away from the camera
            current_vertex.z += 5; // ?? maybe it will be changed in the future

            // store the transformed vertex
            transformed_vertices[j] = current_vertex;
        }

        // starts perform back-face culling algorithm
        vec3_t *vector_a = &transformed_vertices[0]; /**/
        vec3_t *vector_b = &transformed_vertices[1]; /**/
        vec3_t *vector_c = &transformed_vertices[2]; /**/

        vec3_t vector_ba = vec3_subtract(vector_b, vector_a);
        vec3_t vector_ca = vec3_subtract(vector_c, vector_a);

        // remembering the cross product is non-comutative
        // and our engine is using left-handed coordinate system
        vec3_t normal = vec3_cross(&vector_ba, &vector_ca);

        // find the vector between a point in the triangle and the camera origin
        vec3_t camera_ray = vec3_subtract(&camera_position, vector_a);

        // calculate how aligned the camera ray is with the face normal
        // 0 or negative means the face will be hidden
        float aligned_factor = vec3_dot(normal, camera_ray);

        if (aligned_factor < 0) { continue; }

        for (int j = 0; j < 3; j++) {
            vec2_t projected_point = project(transformed_vertices[j]);

            // scale and translate to center
            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }

        ARRAY_PUSH(triangles_to_render, projected_triangle);
    }

}

void render() {
    // colorbuffer - an array of colors e.g. 0xFFFF0000
    // 0x = hex number
    // 0xFF|FF|00|00
    //   A  R  G  B
    // ...
    clear_color_buffer(0xFF000000);

    draw_grid(10);

    const int face_amount = ARRAY_SIZE(triangles_to_render);
    for(int i = 0; i < face_amount; i++) {
        const triangle_t current_triangle = triangles_to_render[i];
        for (int point = 0; point < 3; point++) {
            draw_rect(current_triangle.points[point].x,
                      current_triangle.points[point].y,
                      4,
                      4,
                      0xFFFF5050
            );
        }

        // draw line
        draw_line(
            current_triangle.points[0].x,
            current_triangle.points[0].y,
            current_triangle.points[1].x,
            current_triangle.points[1].y,
            0xFFFF5050
        );

        draw_line(
            current_triangle.points[1].x,
            current_triangle.points[1].y,
            current_triangle.points[2].x,
            current_triangle.points[2].y,
            0xFFFF5050
        );

        draw_line(
            current_triangle.points[2].x,
            current_triangle.points[2].y,
            current_triangle.points[0].x,
            current_triangle.points[0].y,
            0xFFFF5050
        );
    }

    render_color_buffer();

    SDL_RenderPresent(renderer);
}

void free_resources(void) {
    printf("Destroy resources was called\n");
    ARRAY_DESTROY(mesh.faces);
    ARRAY_DESTROY(mesh.vertices);
    ARRAY_DESTROY(triangles_to_render);
    free(triangles_to_render);
    free(color_buffer);
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
    free_resources();

    return 0;
}
