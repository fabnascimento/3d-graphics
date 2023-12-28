//
// Created by ffnas on 2023-12-28.
//

#include "mesh.h"

vec3_t mesh_vertices[MESH_VERTICES_AMOUNT] = {
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
face_t mesh_faces[MESH_FACE_AMOUNT] = {
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