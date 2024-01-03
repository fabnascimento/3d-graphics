//
// Created by ffnas on 2023-12-28.
//

#include "mesh.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dynamic_array.h"

char *VERTEX_FORMAT = "%*s %f %f %f";
char *FACES_FORMAT_VERTEXONLY = "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d";
char *FACES_FORMAT_FULL = "%*s %d/%d/%d %d/%d/%d %d/%d/%d";

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

bool load_obj_file(const char* file_name) {

    FILE *file = NULL; // file handle -> reference to the file
    fopen_s(&file, file_name, "r"); // open the file in a mode, in this case read mode

    if (file == NULL) {
        printf("File %s could not be loaded", file_name);
        return false;
    }

    ARRAY_INIT(vec3_t, mesh.vertices);
    ARRAY_INIT(face_t, mesh.faces);

    char line[1024];

    while(fgets(line, 1024, file)) {
        // Vertex info
        if (strncmp(line, "v ", 2) == 0) {
            vec3_t loaded_vertex;
            sscanf_s(line, VERTEX_FORMAT, &loaded_vertex.x, &loaded_vertex.y, &loaded_vertex.z);
            ARRAY_PUSH(mesh.vertices, loaded_vertex);
        }

        // Face info
        if (strncmp(line, "f ", 2) == 0) {
            int vertex_indices[3];
            int texture_indices[3];
            int normal_indices[3];

            sscanf_s(
                line, FACES_FORMAT_FULL,
                &vertex_indices[0], &texture_indices[0], &normal_indices[0],
                &vertex_indices[1], &texture_indices[1], &normal_indices[1],
                &vertex_indices[2], &texture_indices[2], &normal_indices[2]
            );

            face_t loaded_face = {
                .a = vertex_indices[0],
                .b = vertex_indices[1],
                .c = vertex_indices[2]
            };

            ARRAY_PUSH(mesh.faces, loaded_face);
        }

    }

    fclose(file);

    return true;
}