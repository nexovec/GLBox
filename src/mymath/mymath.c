#include "mymath.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdint.h"

// SECTION: Vec3f
Vec3f *Vec3f_print(Vec3f* vec){
    printf("(%f,%f,%f)\n",vec->x,vec->y,vec->z);
    return vec;
}
Vec3f *Vec3f_fromFloatArr(Vec3f *vecArr, float *floatArr, uint32_t num){
    for(int i = 0;i<num;i++){
        vecArr[i].x = floatArr[i*3];
        vecArr[i].y = floatArr[i*3+1];
        vecArr[i].z = floatArr[i*3+2];
        // Vec3f_print(&vecArr[i]);
    }
}

// SECTION: Mat4f
// TODO: remake without allocations
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
Mat4f *Mat4f_rotationX(float rot){
    // TODO: test
    Mat4f *res = Mat4f_identity();
    float c = (float)cos(rot);
    float s = (float)sin(rot);
    res->members[5] = c;
    res->members[6] = s;
    res->members[9] = -s;
    res->members[10] = c;
    return res;
}
Mat4f *Mat4f_rotationY(float rot){
    // TODO: test
    Mat4f *res = Mat4f_identity();
    float c = (float)cos(rot);
    float s = (float)sin(rot);
    res->members[0] = c;
    res->members[2] = -s;
    res->members[8] = s;
    res->members[10] = c;
    return res;
}
Mat4f *Mat4f_rotationZ(float rot){
    // TODO: test
    Mat4f *res = Mat4f_identity();
    float c = (float)cos(rot);
    float s = (float)sin(rot);
    res->members[0] = c;
    res->members[1] = s;
    res->members[4] = -s;
    res->members[5] = c;
    return res;
}
Mat4f *Mat4f_rotation(float rotX, float rotY, float rotZ){
// FIXME: leaks
// FIXME: slow
    return Mat4f_multiply(Mat4f_rotationX(rotX), Mat4f_multiply(Mat4f_rotationY(rotY), Mat4f_rotationZ(rotZ)));
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
        res = res & (a->members[i] == b->members[i]);
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