#pragma once
#include "graphics/graphics.h"
#include "mymath/mymath.h"

Mesh *makeTriangleMesh(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f *color);
Mesh *makeQuadMesh(Vec3f *pos, Vec3f *size, int);

// temporary
Mesh *makeSimpleTriangleMesh();
Mesh *makeSimpleQuadMesh();