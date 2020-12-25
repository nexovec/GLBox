#include "mymath.h"
#include "stdlib.h"
#include "stdio.h"

// NOTE: No side effects here!
Mat4f *Mat4f_print(Mat4f *mat)
{
    for (int i = 0; i < 4; i++)
    {
        printf("%f %f %f %f\n", mat->members[4 * i + 0], mat->members[4 * i + 1], mat->members[4 * i + 2], mat->members[4 * i + 3]);
    }
    return mat;
}
int Mat4f_equals(Mat4f *a, Mat4f *b)
{
    int res = 1;
    for (int i = 0; i < 16; i++)
    {
        res = res & (a->members[i] == b->members[i]);
    }
    return res;
}
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
    for (int i = 0; i < 16; i++)
    {
        for (int ii = 0; ii < 4; ii++)
        {
            res->members[i] += a->members[((int)i / 4) + ii] * b->members[((int)i % 4) + ii * 4];
        }
    }
    return a;
}
Mat4f *Mat4f_transpose(Mat4f *mat)
{
    Mat4f *res = Mat4f_zeroes();
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            res->members[y + x * 4] = mat->members[x + y * 4];
    return res;
}