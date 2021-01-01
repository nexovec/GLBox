#pragma once
#include "stdint.h"
// SECTION: Vec3f
typedef struct Vec3f
{
    float x;
    float y;
    float z;
} Vec3f;

Vec3f *Vec3f_print(Vec3f *vec);
Vec3f *Vec3f_fromFloatArr(Vec3f *s_e_vecArr, float *floatArr, uint32_t num);

float Vec3f_dot(Vec3f *a, Vec3f *b);
Vec3f *Vec3f_mult(Vec3f *s_e_vec, Vec3f *b);

// SECTION: Mat4f
typedef struct Mat4f
{
    float members[16];
} Mat4f;

Mat4f *Mat4f_zeroes(Mat4f *mat);
Mat4f *Mat4f_identity(Mat4f *mat);
Mat4f *Mat4f_ortho(Mat4f *mat, float right, float left, float top, float bottom, float far, float near);
Mat4f *Mat4f_translation(Mat4f *mat, float moveX, float moveY, float moveZ);
Mat4f *Mat4f_rotationX(Mat4f *mat, float rot);
Mat4f *Mat4f_rotationY(Mat4f *mat, float rot);
Mat4f *Mat4f_rotationZ(Mat4f *mat, float rot);
Mat4f *Mat4f_rotation(Mat4f *mat, float rotX, float rotY, float rotZ);

Mat4f *Mat4f_print(Mat4f *mat);
int Mat4f_equals(Mat4f *a, Mat4f *b);

Mat4f *Mat4f_add(Mat4f *, Mat4f *);
Mat4f *Mat4f_multiply(Mat4f *dest, Mat4f *a, Mat4f *b);
Mat4f *Mat4f_transpose(Mat4f *dest, Mat4f *mat);