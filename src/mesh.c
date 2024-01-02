//
// Created by ffnas on 2023-12-28.
//

#include "mesh.h"

#include "dynamic_array.h"

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {0, 0, 0}
};

vec3_t cube_vertices[CUBE_VERTICES_AMOUNT] = {
    {-1, -1, -1}, // 1
    {-1, 1, -1}, // 2
    {1, 1, -1}, // 3
    {1, -1, -1}, // 4
    {1, 1, 1}, // 5
    {1, -1, 1}, // 6
    {-1, 1, 1},
    {-1, -1, 1}
};

// index starting at 1, might be related to OBJ
face_t cube_faces[CUBE_FACES_AMOUNT] = {
    // front
    {1, 2, 3},
    {1, 3, 4},
    // right
    {4, 3, 5},
    {4, 5, 6},
    // back
    {6, 5, 7},
    {6, 7, 8},
    // left
    {8, 7, 2},
    {8, 2, 1},
    // top
    {2, 7, 5},
    {2, 5, 3},
    // bottom
    {6, 8, 1},
    {6, 1, 4}
};

void load_cube_mesh_data() {
    ARRAY_INIT(vec3_t, mesh.vertices);
    ARRAY_INIT(face_t, mesh.faces);

    for (int i = 0; i < CUBE_VERTICES_AMOUNT; i++) {
        const vec3_t cube_vertex = cube_vertices[i];
        ARRAY_PUSH(mesh.vertices, cube_vertex);
    }

    for (int i = 0; i < CUBE_FACES_AMOUNT; i++) {
        const face_t cube_face = cube_faces[i];
        ARRAY_PUSH(mesh.faces, cube_face);
    }
}