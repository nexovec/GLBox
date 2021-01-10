#include "graphics/graphics.h"
#include "stdlib.h"
Mesh *makeTriangleMesh(float x1, float y1, float x2, float y2, float x3, float y3, float color)
{
    // FIXME: leaks
    // FIXME: assumes VBLayout
    Mesh *res = malloc(sizeof(Mesh));
    res->pointer = malloc(3 * (3 * 2) * sizeof(float));
    float *p = res->pointer;
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
    return res;
}
Mesh *makeSimpleTriangleMesh(){
    return makeTriangleMesh(0,0,350,350,0,350,0.8f);
}