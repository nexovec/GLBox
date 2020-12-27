#include "mymath.h"
#include "stdlib.h"
#include "stdio.h"

// NOTE: No side effects here!

Mat4f *Mat4f_zeroes()
{
    Mat4f *res = (Mat4f *)malloc(sizeof(Mat4f));
    for (int i = 0; i < 16; i++)
        res->members[i] = 0;
    return res;
}
Mat4f *Mat4f_identity()
{
    Mat4f *res = Mat4f_zeroes();
    for (int i = 0; i < 16; i++)
        if (i % 4 == ((int)i / 4))
            res->members[i] = 1;
    return res;
};
Mat4f *Mat4f_ortho(float right, float left, float top, float bottom, float far, float near)
{
    Mat4f *res = Mat4f_zeroes();
    res->members[0] = 2.f / (right - left);
    res->members[5] = 2.f / (top - bottom);
    res->members[10] = 2.f / (near - far);
    res->members[15] = 1;
    res->members[14] = -(far + near) / (far - near);
    res->members[13] = -(top + bottom) / (top - bottom);
    res->members[12] = -(right + left) / (right - left);
    Mat4f_print(res);
    return res;
}
Mat4f *Mat4f_translation(float moveX, float moveY, float moveZ)
{
    Mat4f *res = Mat4f_identity();
    res->members[14] = moveZ;
    res->members[13] = moveY;
    res->members[12] = moveX;
    return res;
}

Mat4f *Mat4f_print(Mat4f *mat)
{
    for (int i = 0; i < 4; i++)
    {
        printf("%f %f %f %f\n", mat->members[4 * 0 + i], mat->members[4 * 1 + i], mat->members[4 * 2 + i], mat->members[4 * 3 + i]);
    }
    return mat;
}
int Mat4f_equals(Mat4f *a, Mat4f *b)
{
    int res = 1;
    for (int i = 0; i < 16; i++)
    {
        res & (a->members[i] == b->members[i]);
    }
    return res;
}
Mat4f *Mat4f_copy(Mat4f *mat)
{
    Mat4f *res = (Mat4f *)malloc(sizeof(Mat4f));
    for (int i = 0; i < 16; i++)
        res->members[i] = mat->members[i];
    return res;
}

Mat4f *Mat4f_add(Mat4f *a, Mat4f *b)
{
    Mat4f *res = (Mat4f *)malloc(sizeof(Mat4f));
    for (int i = 0; i < 16; i++)
        res->members[i] = a->members[i] + b->members[i];
    return res;
}
Mat4f *Mat4f_multiply(Mat4f *a, Mat4f *b)
{
    Mat4f *res = Mat4f_zeroes();
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            for (int i = 0; i < 4; i++)
                res->members[y + x * 4] += a->members[x * 4 + i] * b->members[y + i * 4];
    return res;
}
Mat4f *Mat4f_transpose(Mat4f *mat)
{
    Mat4f *res = Mat4f_zeroes();
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            res->members[y + x * 4] = mat->members[x + y * 4];
    return res;
}