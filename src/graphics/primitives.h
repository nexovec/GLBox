#pragma once
#include "graphics/graphics.h"
#include "mymath/mymath.h"

Mesh *makeTriangleMesh(float x1, float y1, float x2, float y2, float x3, float y3, Vec3f *color);
Mesh *makeQuadMesh(Vec3f *pos, Vec3f *size);

// temporary
Mesh *makeSimpleTriangleMesh();
Mesh *makeSimpleQuadMesh();