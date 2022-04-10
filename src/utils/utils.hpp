#pragma once
#include "glad/glad.h"
#include "mymath/mymath.hpp"
#include <stdint.h>
#include <string>

struct File_Container
{
    bool file_loaded;
    size_t buffer_size;
    size_t data_size;
    char *data;
};
File_Container read_file(const char *path);

void glfw_err_callback(int code, char *err);

void utils_print_GL_error(const uint32_t subject, GLenum pname, char *prefixedMessage);
// const uint32_t gl_build_program(char *vertPath, char *fragPath);
const uint32_t gl_build_program(const char * const vertPath, const char * const fragPath);

float *concat_float_arrays(float *a, size_t aCount, float *b, size_t bCount);

Vec3f *color_vec_from_enum(Vec3f *colorVec, int col);
void print_float_arr(float *arr, int n);