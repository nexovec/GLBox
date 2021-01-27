#include "graphics.h"
#include "mymath/mymath.h"
#include "utils/utils.h"
#include "stdlib.h"

// FIXME: assumes VBLayout
float *makeTriangleArr(Vec3f *v1, Vec3f *v2, Vec3f *v3, Vec3f *color)
{
    float *p = malloc(3 * (3 * 2) * sizeof(float));
    p[0] = v1->x;
    p[1] = v1->y;
    p[2] = p[8] = p[14] = 0.f;
    p[6] = v2->x;
    p[7] = v2->y;
    p[12] = v3->x;
    p[13] = v3->y;
    for (int i = 0; i < 3; i++)
        for (int ii = 0; ii < 3; ii++)
            p[i * 6 + 3 + ii] = ((float *)color)[ii];
    // TODO: vCount
    return p;
}

Mesh *makeQuadMesh(Vec3f *pos, Vec3f *size, int col)
{
    // FIXME: leaks
    Mesh *res = malloc(sizeof(Mesh));
    Vec3f colorVec;
    colorVecFromEnum(&colorVec, col);
    res->pointer = concatFloatArrays(
        makeTriangleArr(
            &(Vec3f){pos->x, pos->y, 0},
            &(Vec3f){pos->x + size->x, pos->y + size->y, 0},
            &(Vec3f){pos->x, pos->y + size->y, 0},
            &colorVec),
        18,
        makeTriangleArr(
            &(Vec3f){pos->x, pos->y, 0},
            &(Vec3f){pos->x + size->x, pos->y, 0},
            &(Vec3f){pos->x + size->x, pos->y + size->y, 0},
            &colorVec),
        18);
    res->vCount = 6;
    return res;
}

// temporary
Mesh *makeSimpleTriangleMesh()
{
    // FIXME: leaks
    Mesh *res = malloc(sizeof(Mesh));
    res->pointer = makeTriangleArr(&(Vec3f){20, 20, 0}, &(Vec3f){350, 350, 0}, &(Vec3f){20, 350, 0}, &(Vec3f){0.8f, 0.4f, 0.2f});
    return res;
}
// temporary
Mesh *makeSimpleQuadMesh()
{
    Mesh *m1 = makeQuadMesh(&(Vec3f){20, 20, 0}, &(Vec3f){350, 350, 0}, COLOR_BLUE);
    Mesh *m2 = makeQuadMesh(&(Vec3f){400, 400, 0}, &(Vec3f){100, 100, 0}, COLOR_BLACK);
    // FIXME: leaks
    Mesh *res = malloc(sizeof(Mesh));
    // FIXME: magic numbers
    res->pointer = concatFloatArrays(m1->pointer, 6 * m1->vCount, m2->pointer, 6 * m2->vCount);
    res->vCount = m1->vCount + m2->vCount;
    return res;
}