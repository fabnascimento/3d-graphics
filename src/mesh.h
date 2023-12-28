//
// Created by ffnas on 2023-12-28.
//


#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define MESH_VERTICES_AMOUNT 8
extern vec3_t mesh_vertices[MESH_VERTICES_AMOUNT];
#define MESH_FACE_AMOUNT 12
extern face_t mesh_faces[MESH_FACE_AMOUNT];

#endif //MESH_H
