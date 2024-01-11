//
// Created by ffnas on 2023-12-28.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include <stdint.h>

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

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif //TRIANGLE_H
