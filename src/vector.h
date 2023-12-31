//
// Created by ffnas on 12/14/2023.
//

#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
} vec2_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

/* VEC2 functions */
float vec2_length(vec2_t vector);

/* VEC3 functions */
float vec3_length(vec3_t vector);

vec3_t vec3_rotate_x(vec3_t original, float angle);
vec3_t vec3_rotate_y(vec3_t original, float angle);
vec3_t vec3_rotate_z(vec3_t original, float angle);

#endif //VECTOR_H
