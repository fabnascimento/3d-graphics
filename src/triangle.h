//
// Created by ffnas on 2023-12-28.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

// stores vertex index
typedef struct {
    int a;
    int b;
    int c;
} face_t;

// stores projected vec2 points
typedef struct {
    vec2_t points[3];
} triangle_t;

#endif //TRIANGLE_H
