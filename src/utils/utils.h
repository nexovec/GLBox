#pragma once
#include "glad/glad.h"
#include "stdint.h"
char *readStringFromFile(char *path);

void glfw_errCbck(int code, char *err);

void gl_printGLError(const uint32_t subject, GLenum pname, char *prefixedMessage);
const uint32_t gl_buildProgram(char *vertPath, char *fragPath);