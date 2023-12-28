//
// Created by ffnas on 12/14/2023.
//

#include "vector.h"

#include <math.h>


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