#include "mymath.h"
#include "stdlib.h"
#include "stdio.h"

// NOTE: No side effects here!
Mat4f* Mat4f_print(Mat4f* mat){
    for(int i = 0;i<4;i++){
        printf("%f %f %f %f\n",mat->members[4*i + 0], mat->members[4*i + 1], mat->members[4*i + 2], mat->members[4*i + 3]);
    }
    return mat;
}
Mat4f* Mat4f_zeroes(){
    Mat4f* res = (Mat4f*)malloc(sizeof(Mat4f));
    for(int i = 0;i<16;i++)res->members[i] = 0;
    return res;
}
Mat4f* Mat4f_identity(){
    Mat4f* res = Mat4f_zeroes();
    for(int i = 0;i<16;i++)if(i%4==((int)i/4))res->members[i] = 1;
    return res;
};
Mat4f* Mat4f_add(Mat4f* a,Mat4f* b){
    return a;
}
Mat4f* Mat4f_multiply(Mat4f* a, Mat4f* b){
    return a;
}
Mat4f* Mat4f_transpose(Mat4f* mat){
    return mat;
}