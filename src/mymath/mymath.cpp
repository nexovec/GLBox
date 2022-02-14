#include "pch.hpp"
#include "mymath.hpp"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdint.h"

// SECTION: Vec3f
Vec3f *Vec3f_print(Vec3f *vec)
{
    printf("(%f,%f,%f)\n", vec->x, vec->y, vec->z);
    return vec;
}
Vec3f *Vec3f_fromFloatArr(Vec3f *s_e_vecArr, float *floatArr, uint32_t num)
{
    for (uint32_t i = 0; i < num; i++)
    {
        s_e_vecArr[i].x = floatArr[i * 3];
        s_e_vecArr[i].y = floatArr[i * 3 + 1];
        s_e_vecArr[i].z = floatArr[i * 3 + 2];
    }
    return s_e_vecArr;
}

float Vec3f_dot(Vec3f *a, Vec3f *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}
Vec3f *Vec3f_mult(Vec3f *s_e_vec, Vec3f *b)
{
    s_e_vec->x *= b->x;
    s_e_vec->y *= b->y;
    s_e_vec->z *= b->z;
    return s_e_vec;
}

// SECTION: Mat4f
Mat4f *Mat4f_zeroes(Mat4f *dest)
{
    for (int i = 0; i < 16; i++)
        dest->members[i] = 0;
    return dest;
}
Mat4f *Mat4f_identity(Mat4f *s_e_mat)
{
    Mat4f_zeroes(s_e_mat);
    for (int i = 0; i < 16; i++)
        if (i % 4 == ((int)i / 4))
            s_e_mat->members[i] = 1;
    return s_e_mat;
};
Mat4f *Mat4f_ortho(Mat4f *mat, float right, float left, float top, float bottom, float far, float near)
{
    Mat4f_zeroes(mat);
    mat->members[0] = 2.f / (right - left);
    mat->members[5] = 2.f / (top - bottom);
    mat->members[10] = 2.f / (near - far);
    mat->members[15] = 1;
    mat->members[14] = -(far + near) / (far - near);
    mat->members[13] = -(top + bottom) / (top - bottom);
    mat->members[12] = -(right + left) / (right - left);
    return mat;
}
Mat4f *Mat4f_translation(Mat4f *s_e_mat, float moveX, float moveY, float moveZ)
{
    Mat4f_identity(s_e_mat);
    s_e_mat->members[14] = moveZ;
    s_e_mat->members[13] = moveY;
    s_e_mat->members[12] = moveX;
    return s_e_mat;
}
Mat4f *Mat4f_rotationX(Mat4f *s_e_mat, float rot)
{
    Mat4f_identity(s_e_mat);
    float c = (float)cos(rot);
    float s = (float)sin(rot);
    s_e_mat->members[5] = c;
    s_e_mat->members[6] = s;
    s_e_mat->members[9] = -s;
    s_e_mat->members[10] = c;
    return s_e_mat;
}
Mat4f *Mat4f_rotationY(Mat4f *s_e_mat, float rot)
{
    Mat4f_identity(s_e_mat);
    float c = (float)cos(rot);
    float s = (float)sin(rot);
    s_e_mat->members[0] = c;
    s_e_mat->members[2] = -s;
    s_e_mat->members[8] = s;
    s_e_mat->members[10] = c;
    return s_e_mat;
}
Mat4f *Mat4f_rotationZ(Mat4f *s_e_mat, float rot)
{
    Mat4f_identity(s_e_mat);
    float c = (float)cos(rot);
    float s = (float)sin(rot);
    s_e_mat->members[0] = c;
    s_e_mat->members[1] = s;
    s_e_mat->members[4] = -s;
    s_e_mat->members[5] = c;
    return s_e_mat;
}
Mat4f *Mat4f_rotation(Mat4f *mat, float rotX, float rotY, float rotZ)
{
    // FIXME: slow
    Mat4f x, y, z, yz;
    Mat4f_rotationX(&x, rotX);
    Mat4f_rotationY(&y, rotY);
    Mat4f_rotationZ(&z, rotZ);
    Mat4f_multiply(&yz, &y, &z);
    Mat4f_multiply(mat, &x, &yz);
    return mat;
}

Mat4f *Mat4f_print(Mat4f *mat)
{
    for (int i = 0; i < 4; i++)
    {
        printf("|%6.4f %6.4f %7.4f %7.4f|\n", mat->members[4 * 0 + i], mat->members[4 * 1 + i], mat->members[4 * 2 + i], mat->members[4 * 3 + i]);
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
Mat4f *Mat4f_copy(Mat4f *s_e_dest, Mat4f *mat)
{
    for (int i = 0; i < 16; i++)
        s_e_dest->members[i] = mat->members[i];
    return s_e_dest;
}

Mat4f *Mat4f_add(Mat4f *s_e_mat, Mat4f *b)
{
    for (int i = 0; i < 16; i++)
        s_e_mat->members[i] += b->members[i];
    return s_e_mat;
}
Mat4f *Mat4f_multiply(Mat4f *dest, Mat4f *a, Mat4f *b)
{
    Mat4f res;
    Mat4f_zeroes(&res);
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            for (int i = 0; i < 4; i++)
                res.members[y + x * 4] += a->members[x * 4 + i] * b->members[y + i * 4];
    return Mat4f_copy(dest, &res);
}
Mat4f *Mat4f_transpose(Mat4f *dest, Mat4f *mat)
{
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            dest->members[y + x * 4] = mat->members[x + y * 4];
    return dest;
}