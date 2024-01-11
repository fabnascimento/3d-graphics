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

I am following the course choice of using the technique called flat-bottom and flat-top.
This technique divides the triangle into two triangles, one being the flat-bottom one, and the other being the flat-top

to perform this division we need to find the midpoint of the original triangle

$M_y = y1$ y1 -> being the point in the middle of the triangle