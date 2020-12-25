#pragma once
typedef struct Mat4f{
    float members[16];
}Mat4f;
Mat4f* Mat4f_print();
Mat4f* Mat4f_zeroes();
Mat4f* Mat4f_identity();
Mat4f* Mat4f_multiply(Mat4f*,Mat4f*);
Mat4f* Mat4f_transpose(Mat4f*);