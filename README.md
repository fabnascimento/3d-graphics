# 3d-graphics

Find the normal

Cross Product between vertices

## Cross Product

The result is another vector

## Dot Product

The result of a dot product is a float value

- "projection of a vector over another if they are unit vectors"
- "how aligned those two vectors are"

## Back-face Culling

1. Find vectors `B-A` and `C-A`
2. Take their cross product and find the perpendicular normal `N`
3. Find the camera ray vector by `subtracting` the `camera position` from point `A`
4. Take the `dot product` between the normal `N` and the `camera ray`
5. If this dot product is less than `zero`, then we `do not` display the face


## Triangle Rasterization

I am following the course's choice of using the technique called flat-bottom and flat-top.
This technique divides the triangle into two triangles, one being the flat-bottom one, and the other being the flat-top

to perform this division we need to find the midpoint of the original triangle

$M_y = y1$ y1 -> being the point in the middle of the triangle

### interesting discovery

One of the students from the course asked why not use draw_pixel directly instead of calling the draw_line function
in each inner triangle functions (flat-bottom & flat-top).

After investigating with a specific triangle I could notice that for some cases the slop calculation that is tied to the
x_start will make the `x_start` to grow bigger than `x_end` before the entire triangle gets drawn onto the screen.

```c++
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
```

```c++
// this is an example of a difficult triangle to render if I just loop
// the x value horizontally
 draw_filled_triangle(1074, 403, 874, 375, 1138, 599, 0xFF00FF00);
 draw_rect(1074, 403, 5, 5, 0xFF00FF00);
 draw_rect(874, 375, 5, 5, 0xFF00FF00);
 draw_rect(1138, 599, 5, 5, 0xFF00FF00);
 draw_rect(907, 403, 5, 5, 0xFFFFFF00);
 draw_triangle(1138, 599, 1074, 403, 907, 403, color_array[0]);
 draw_triangle(874, 375, 1074, 403, 907, 403, color_array[3]);

 draw_filled_triangle(874, 375, 1074, 403, 907, 403, 0xFFFFFF00);
```

## Proposed challenge 

At the course they proposed a challenge of Selecting Different Rendering Modes by the keyboard

I plan to make use of the `command` design pattern as I was learning about it on the book
`Game Programming Patterns` by `Robert Nystrom`.



