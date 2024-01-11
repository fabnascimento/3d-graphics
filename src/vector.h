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
float vec2_length(const vec2_t* vector);

void vec2_normalize(vec2_t* v);

vec2_t vec2_add(const vec2_t* vec1, const vec2_t* vec2);

vec2_t vec2_subtract(vec2_t* vec1, vec2_t* vec2);

vec2_t vec2_multiply(const vec2_t* v, float scalar);

float vec2_dot(const vec2_t* a, const vec2_t* b);

vec2_t vec2_divide(const vec2_t v, float scalar);

/* VEC3 functions */
float vec3_length(const vec3_t* vector);

void vec3_normalize(vec3_t* v);

vec3_t vec3_add(const vec3_t* a, const vec3_t* b);

vec3_t vec3_subtract(const vec3_t* a, const vec3_t* b);

vec3_t vec3_multiply(const vec3_t* v, float scalar);

vec3_t vec3_divide(const vec3_t* v, float scalar);

vec3_t vec3_cross(vec3_t* a, vec3_t* b);

float vec3_dot(vec3_t a, vec3_t b);


vec3_t vec3_rotate_x(vec3_t original, float angle);

vec3_t vec3_rotate_y(vec3_t original, float angle);

vec3_t vec3_rotate_z(vec3_t original, float angle);

#endif //VECTOR_H
