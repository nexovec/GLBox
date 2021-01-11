#include "graphics/graphics.h"
#include "utils/utils.h"
#include "stdlib.h"

// FIXME: assumes VBLayout

float *makeTriangleArr(float x1, float y1, float x2, float y2, float x3, float y3, float color)
{
    float *p = malloc(3 * (3 * 2) * sizeof(float));
    p[0] = x1;
    p[1] = y1;
    p[2] = p[8] = p[14] = 0.f;
    p[6] = x2;
    p[7] = y2;
    p[12] = x3;
    p[13] = y3;
    for (int i = 0; i < 3; i++)
        for (int ii = 0; ii < 3; ii++)
            p[i * 6 + 3 + ii] = color;
    // TODO: vCount
    return p;
}

Mesh *makeQuadMesh(float x, float y, float width, float height)
{
    // FIXME: leaks
    Mesh *res = malloc(sizeof(Mesh));
    res->pointer = concatArrays(
        makeTriangleArr(x, y, x + width, y + height, x, y + height, 0.8f), 18,
        makeTriangleArr(x, y, x + width, y, x + width, y + height, 0.8f), 18);
    return res;
}

// temporary
Mesh *makeSimpleTriangleMesh()
{
    // FIXME: leaks
    Mesh *res = malloc(sizeof(Mesh));
    res->pointer = makeTriangleArr(20, 20, 350, 350, 20, 350, 0.8f);
    return res;
}
Mesh *makeSimpleQuadMesh()
{
    return makeQuadMesh(20, 20, 350, 350);
}