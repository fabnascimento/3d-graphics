//
// Created by ffnas on 2023-12-28.
//


#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define CUBE_VERTICES_AMOUNT 8
extern vec3_t cube_vertices[CUBE_VERTICES_AMOUNT];
#define CUBE_FACES_AMOUNT 12
extern face_t cube_faces[CUBE_FACES_AMOUNT];

typedef struct {
    face_t* faces; // dynamic array of faces
    vec3_t* vertices; // dynamic array of vertices
    vec3_t rotation; // rotation euler angles
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data();

#endif //MESH_H
