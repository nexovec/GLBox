#pragma once
#include "glad/glad.h"
#include "mymath/mymath.hpp"
#include <stdint.h>
#include <string>
char *readStringFromFile(char *path);

void glfw_errCbck(int code, char *err);

void gl_printGLError(const uint32_t subject, GLenum pname, char *prefixedMessage);
// const uint32_t gl_buildProgram(char *vertPath, char *fragPath);
const uint32_t gl_buildProgram(const char * const vertPath, const char * const fragPath);

float *concatFloatArrays(float *a, size_t aCount, float *b, size_t bCount);

Vec3f *colorVecFromEnum(Vec3f *colorVec, int col);
void printFloatArr(float *arr, int n);