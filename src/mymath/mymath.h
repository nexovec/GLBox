#pragma once
#include "stdint.h"
// SECTION: Vec3f
typedef struct Vec3f{
    float x;
    float y;
    float z;
}Vec3f;

Vec3f *Vec3f_fromFloatArr(Vec3f *vecArr, float *floatArr, uint32_t num);

// SECTION: Mat4f
typedef struct Mat4f
{
    float members[16];
} Mat4f;

Mat4f *Mat4f_zeroes();
Mat4f *Mat4f_identity();
Mat4f *Mat4f_ortho(float right, float left, float top, float bottom, float far, float near);
Mat4f *Mat4f_translation(float moveX, float moveY, float moveZ);
Mat4f *Mat4f_rotationX(float rot);
Mat4f *Mat4f_rotationY(float rot);
Mat4f *Mat4f_rotationZ(float rot);
Mat4f *Mat4f_rotation(float rotX, float rotY, float rotZ);

Mat4f *Mat4f_print(Mat4f *);
int Mat4f_equals(Mat4f *, Mat4f *);

Mat4f *Mat4f_add(Mat4f *, Mat4f *);
Mat4f *Mat4f_multiply(Mat4f *, Mat4f *);
Mat4f *Mat4f_transpose(Mat4f *);