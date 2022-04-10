#define _CRT_SECURE_NO_WARNINGS
#include "pch.hpp"
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

// data container might be bigger than what is read
File_Container read_file(const char *path)
{
    FILE *file_handle = fopen(path, "r");
    if (file_handle == NULL)
    {
        return {};
    }
    fseek(file_handle, 0, SEEK_END);
    size_t reported_file_size = ftell(file_handle);
    size_t buffer_size = reported_file_size + 1;
    assert(buffer_size <= UINT32_MAX);
    fseek(file_handle, 0, SEEK_SET);
    // char *contents = (char *)malloc(buffer_size * sizeof(char));
    char *contents = (char *)calloc(buffer_size, sizeof(char));
    assert(contents);
    uint32_t size_read = fread_s(contents, (uint32_t)reported_file_size, sizeof(char), (uint32_t)reported_file_size, file_handle);
    // contents[reported_file_size] = 0;
    // contents[size_read] = 0;
    assert(reported_file_size >= size_read);
    // NOTE: If this errors, read error occurred
    // std::cout << "File reported_file_size: " << reported_file_size << "\n"
    //           << "Actual data reported_file_size: " << size_read << std::endl;
    return {true, buffer_size, size_read, contents};
}
void glfw_err_callback(int code, char *err)
{
    fprintf(stderr, "GLFW Error %d: %s\n", code, err);
}
void utils_print_GL_error(const uint32_t subject, GLenum pname, char *prefixedMessage)
{
    uint32_t result;
    glGetShaderiv(subject, pname, (GLint *)&result);
    if (!result)
    {
        uint32_t maxLength;
        glGetShaderiv(subject, GL_INFO_LOG_LENGTH, (GLint *)&maxLength);
        char *message = (char *)malloc(maxLength * sizeof(char));
        glGetShaderInfoLog(subject, maxLength, (GLint *)&maxLength, message);
        fprintf(stderr, "%s\n%s\n", prefixedMessage, message);
        free(message);
        exit(-1);
    }
}
const uint32_t gl_build_program(const char *const vertPath, const char *const fragPath)
{
    char *vert_shader_source = read_file(vertPath).data;
    char *fragment_shader_source = read_file(fragPath).data;
    // TODO: test fail cases
    if (vert_shader_source == nullptr)
    {
        std::cout << "Shader file " << vert_shader_source << " can't be read." << std::endl;
        terminate();
    }
    else if (fragment_shader_source == nullptr)
    {
        std::cout << "Shader file " << fragment_shader_source << " can't be read." << std::endl;
        terminate();
    }
    const uint32_t v_shader = glad_glCreateShader(GL_VERTEX_SHADER);
    const uint32_t f_shader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(v_shader, 1, &vert_shader_source, NULL);
    glShaderSource(f_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(v_shader);
    glCompileShader(f_shader);
    utils_print_GL_error(v_shader, GL_COMPILE_STATUS, (char *)"Vertex shader Error:");
    utils_print_GL_error(f_shader, GL_COMPILE_STATUS, (char *)"Fragment shader Error:");
    const uint32_t program = glCreateProgram();
    glAttachShader(program, v_shader);
    glAttachShader(program, f_shader);
    glLinkProgram(program);
    utils_print_GL_error(program, GL_LINK_STATUS, (char *)"Linking Error:");
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