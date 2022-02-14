#pragma once
#include "../mymath/mymath.hpp"
#include "graphics/graphics.hpp"

Mesh *make_triangle_mesh(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f *color);
Mesh *make_quad_mesh(Vec3f *pos, Vec3f *size, int col);

// temporary
Mesh *make_simple_triangle_mesh();
Mesh *make_simple_quad_mesh();