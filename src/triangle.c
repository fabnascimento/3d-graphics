//
// Created by ffnas on 2023-12-28.
//

#include "triangle.h"
#include "display.h"

// to move!
void swap(int *a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}

// 1. start from top (x0, y0)
// 2. calculate left and right slopes
// 3. render scanlines looping all y values from top to bottom
// 3.1 define limits x_start and x_end for the scanlines
// 3.2 increment (as the triangle gets bigger) x_start and x_end
void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // calculate inverse of the slope, meaning how much in x we change per y
    float y_slope_left = (float)(x1 - x0) / (y1 - y0);
    float y_slope_right = (float)(x2 - x0) / (y2 - y0);

    float x_start = x0;
    float x_end = x0;

    // loop scanlines from top to bottom
    for(int y = y0; y <= y2; y++) {
        draw_line(x_start, y, x_end, y, color);
        x_start += y_slope_left;
        x_end += y_slope_right;
    }
}

void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    float y_slope_left = (float)(x2 - x0) / (y2 - y0);
    float y_slope_right = (float)(x2 - x1) / (y2 - y1);

    // start at the bottom vertex
    float x_start = x2;
    float x_end = x2;

    for(int y = y2; y >= y0; y--) {
        draw_line(x_start, y, x_end, y, color);
        x_start -= y_slope_left;
        x_end -= y_slope_right;
    }
}


void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // perfoming naive sorting by y-index
    if (y0 > y1) {
        swap(&y0, &y1);
        swap(&x0, &x1);
    }
    if (y1 > y2) {
        swap(&y1, &y2);
        swap(&x1, &x2);
    }
    if (y0 > y1) {
        swap(&y0, &y1);
        swap(&x0, &x1);
    }

    if (y1 == y2) {
        fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
        return;
    }

    if (y0 == y1) {
        fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
        return;
    }

    // calculate the new vertex (Mx, My) using triangle similarity
    int My = y1;
    int Mx = ((float)((x2 - x0) * (y1 - y0)) / (float)(y2 - y0)) + x0;


    fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);

    fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);
}

