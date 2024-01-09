//
// Created by ffnas on 12/14/2023.
//

#include "vector.h"

#include <math.h>

// VEC2 functions

float vec2_length(const vec2_t* vector) {
    return sqrt(vector->x * vector->x + vector->y * vector->y);
}

vec2_t vec2_add(const vec2_t* vec1, const vec2_t* vec2) {
    vec2_t result = {
        .x = vec1->x + vec2->x,
        .y = vec1->y + vec2->y
    };
    return result;
}

vec2_t vec2_subtract(vec2_t* vec1, vec2_t* vec2) {
    vec2_t result = {
        .x = vec1->x - vec2->x,
        .y = vec1->y - vec2->y
    };

    return result;
}

vec2_t vec2_multiply(const vec2_t* v, float scalar) {
    vec2_t result = {
        v->x * scalar,
        v->y * scalar
    };

    return result;
}

vec2_t vec2_divide(const vec2_t v, float scalar) {
    vec2_t result = {
        v.x / scalar,
        v.y / scalar
    };

    return result;
}

float vec2_dot(const vec2_t* a, const vec2_t* b) {
    return a->x * b->x + a->y * b->y;
}

// VEC3 functions
float vec3_length(const vec3_t* vector) {
    return sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}

vec3_t vec3_add(const vec3_t* a, const vec3_t* b) {
    vec3_t result = {
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z
    };

    return result;
}

vec3_t vec3_subtract(const vec3_t* a, const vec3_t* b) {
    vec3_t result = {
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z
    };

    return result;
}

vec3_t vec3_multiply(const vec3_t* v, float scalar) {
    vec3_t result = {
        v->x * scalar,
        v->y * scalar,
        v->z * scalar
    };

    return result;
}

vec3_t vec3_divide(const vec3_t* v, const float scalar) {
    vec3_t result = {
        v->x / scalar,
        v->y / scalar,
        v->z / scalar
    };

    return result;
}

vec3_t vec3_cross(vec3_t* a, vec3_t* b) {
    vec3_t result = {
        .x = a->y * b->z - a->z * b->y,
        .y = a->z * b->x - a->x * b->z,
        .z = a->x * b->y - a->y * b->x
    };
    return result;
}

float vec3_dot(vec3_t a, vec3_t b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vec3_t vec3_rotate_x(vec3_t original, float angle) {
    const vec3_t rotated_vector = {
        .x = original.x,
        .y = original.y * cos(angle) - original.z * sin(angle),
        .z = original.y * sin(angle) + original.z * cos(angle)
    };

    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t original, float angle) {
    const vec3_t rotated_vector = {
        .x = original.x * cos(angle) - original.z * sin(angle),
        .y = original.y,
        .z = original.x * sin(angle) + original.z * cos(angle)
    };

    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t original, float angle) {
    const vec3_t rotated_vector = {
        .x = original.x * cos(angle) - original.y * sin(angle),
        .y = original.x * sin(angle) + original.y * cos(angle),
        .z = original.z
    };

    return rotated_vector;
}