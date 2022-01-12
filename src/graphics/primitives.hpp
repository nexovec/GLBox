#pragma once
#include "../mymath/mymath.hpp"
#include "graphics/graphics.hpp"

Mesh *makeTriangleMesh(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f *color);
Mesh *makeQuadMesh(Vec3f *pos, Vec3f *size, int col);

// temporary
Mesh *makeSimpleTriangleMesh();
Mesh *makeSimpleQuadMesh();