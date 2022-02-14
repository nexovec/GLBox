#define _CRT_SECURE_NO_WARNINGS
#include "utils.hpp"
#include "mymath/mymath.hpp"
#include "graphics/graphics.hpp"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "glad/glad.h"
#include <fstream>
#include <cassert>
#include <iostream>

// TODO: test performance
// char *read_file(const char *path)
// {
//     FILE *file = fopen(path, "r"); // FIXME: fissile material
//     char *contents = (char *)malloc(1000 * sizeof(char));
//     int i = 0;
//     char character;
// while ((character = fgetc(file)) != EOF)
//     {
//         contents[i++] = character;
//     }
//     contents[i] = '\0';
//     fclose(file);
//     return contents;
// }
char *read_file(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        // TODO: do something
    }
    fseek(file, 0, SEEK_END);
    uint32_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *contents = (char *)malloc((size) * sizeof(char));
    assert(contents);
    uint32_t end_char = fread_s(contents, size, sizeof(char), size, file);
    // NOTE: This errors if fread read more characters than size
    assert(size >= end_char + 1);
    contents[end_char] = '\0';
    return contents;
}
void glfw_err_callback(int code, char *err)
{
    fprintf(stderr, "GLFW Error %d: %s\n", code, err);
}
void gl_print_GL_error(const uint32_t subject, GLenum pname, char *prefixedMessage)
{
    uint32_t result;
    glad_glGetShaderiv(subject, pname, (GLint *)&result);
    if (!result)
    {
        uint32_t maxLength;
        glad_glGetShaderiv(subject, GL_INFO_LOG_LENGTH, (GLint *)&maxLength);
        char *message = (char *)malloc(maxLength * sizeof(char));
        glad_glGetShaderInfoLog(subject, maxLength, (GLint *)&maxLength, message);
        fprintf(stderr, "%s\n%s\n", prefixedMessage, message);
        free(message);
        exit(-1);
    }
}
const uint32_t gl_build_program(const char *const vertPath, const char *const fragPath)
{
    char *vert_shader_source = read_file(vertPath);
    char *fragment_shader_source = read_file(fragPath);
    const uint32_t v_shader = glad_glCreateShader(GL_VERTEX_SHADER);
    const uint32_t f_shader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(v_shader, 1, &vert_shader_source, NULL);
    glad_glShaderSource(f_shader, 1, &fragment_shader_source, NULL);
    glad_glCompileShader(v_shader);
    glad_glCompileShader(f_shader);
    gl_print_GL_error(v_shader, GL_COMPILE_STATUS, (char *)"Vertex shader Error:");
    gl_print_GL_error(f_shader, GL_COMPILE_STATUS, (char *)"Fragment shader Error:");
    const uint32_t program = glad_glCreateProgram();
    glad_glAttachShader(program, v_shader);
    glad_glAttachShader(program, f_shader);
    glad_glLinkProgram(program);
    gl_print_GL_error(program, GL_LINK_STATUS, (char *)"Linking Error:");
    free(vert_shader_source);
    free(fragment_shader_source);
    return program;
}

float *concat_float_arrays(float *a, size_t aCount, float *b, size_t bCount = 0)
{
    // FIXME: leaks
    float *res = (float *)malloc(sizeof(float) * (aCount + bCount));
    for (int i = 0; i < aCount; i++)
        res[i] = a[i];
    for (int i = 0; i < bCount; i++)
        res[aCount + i] = b[i];
    return res;
}

Vec3f *color_vec_from_enum(Vec3f *colorVec, int col)
{
    switch (col)
    {
    case COLOR_WHITE:
        *colorVec = {0.8f, 0.8f, 0.8f};
        break;
    case COLOR_BLACK:
        *colorVec = {0.12f, 0.12f, 0.12f};
        break;
    case COLOR_BLUE:
        *colorVec = {0.16f, 0.16f, 0.8f};
        break;
    case COLOR_GREEN:
        *colorVec = {0.16f, 0.8f, 0.16f};
        break;
    case COLOR_RED:
        *colorVec = {0.8f, 0.16f, 0.16f};
        break;
    default:
        *colorVec = {1.0f, 0.0f, 1.0f};
        break;
    }
    return colorVec;
}
void print_float_arr(float *arr, int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
        printf("%f, ", arr[i]);
    printf("]");
}