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
