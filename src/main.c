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

float fov_factor = 512;

uint32_t color_array[12] = {
    0xFF485696,
    0xFFE7E7E7,
    0xFFF9C784,
    0xFFFC7A1E,
    0xFFF24C00,
    0xFF00FF00
};

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
    // Wait some time until the reach the target frame time in milliseconds
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    // Only delay execution if we are running too fast
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    previous_frame_time = SDL_GetTicks();

    triangles_to_render = NULL;
    ARRAY_INIT(triangle_t, triangles_to_render);

    mesh.rotation.x += 0.02;
    mesh.rotation.y += 0.01;

    // loop the faces first?
    const int mesh_amount = ARRAY_SIZE(mesh.faces);
    for (int i = 0; i < mesh_amount; i++) {
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];

        vec3_t transformed_vertices[3];

        // Loop all three vertices of this current face and apply transformations
        for (int j = 0; j < 3; j++) {
            vec3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

            // Translate the vertex away from the camera
            transformed_vertex.z += 5;

            // Save transformed vertex in the array of transformed vertices
            transformed_vertices[j] = transformed_vertex;
        }

        // Check backface culling
        vec3_t *vector_a = &transformed_vertices[0]; /*   A   */
        vec3_t *vector_b = &transformed_vertices[1]; /*  / \  */
        vec3_t *vector_c = &transformed_vertices[2]; /* C---B */

        // Get the vector subtraction of B-A and C-A
        vec3_t vector_ab = vec3_subtract(vector_b, vector_a);
        vec3_t vector_ac = vec3_subtract(vector_c, vector_a);
        vec3_normalize(&vector_ab);
        vec3_normalize(&vector_ac);

        // Compute the face normal (using cross product to find perpendicular)
        vec3_t normal = vec3_cross(&vector_ab, &vector_ac);
        vec3_normalize(&normal);

        // Find the vector between vertex A in the triangle and the camera origin
        vec3_t camera_ray = vec3_subtract(&camera_position, vector_a);

        // Calculate how aligned the camera ray is with the face normal (using dot product)
        float dot_normal_camera = vec3_dot(normal, camera_ray);

        // Bypass the triangles that are looking away from the camera
        if (dot_normal_camera < 0) {
            continue;
        }

        triangle_t projected_triangle;

        // Loop all three vertices to perform projection
        for (int j = 0; j < 3; j++) {
            // Project the current vertex
            vec2_t projected_point = project(transformed_vertices[j]);

            // Scale and translate the projected points to the middle of the screen
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

    // this is an example of a difficult triangle to render if I just loop
    // the x value horizontally
    // draw_filled_triangle(1074, 403, 874, 375, 1138, 599, 0xFF00FF00);
    // draw_rect(1074, 403, 5, 5, 0xFF00FF00);
    // draw_rect(874, 375, 5, 5, 0xFF00FF00);
    // draw_rect(1138, 599, 5, 5, 0xFF00FF00);
    // draw_rect(907, 403, 5, 5, 0xFFFFFF00);
    // draw_triangle(1138, 599, 1074, 403, 907, 403, color_array[0]);
    // draw_triangle(874, 375, 1074, 403, 907, 403, color_array[3]);

    // draw_filled_triangle(874, 375, 1074, 403, 907, 403, 0xFFFFFF00);


    const int face_amount = ARRAY_SIZE(triangles_to_render);
    for(int i = 0; i < face_amount; i++) {
        const triangle_t current_triangle = triangles_to_render[i];

        draw_filled_triangle(
            current_triangle.points[0].x, current_triangle.points[0].y,
            current_triangle.points[1].x, current_triangle.points[1].y,
            current_triangle.points[2].x, current_triangle.points[2].y,
            0xFFFF5733
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
