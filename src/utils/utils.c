#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "glad/glad.h"

char* readStringFromFile(char* path){
    FILE* file = fopen(path,"r"); // FIXME: fissile material
    char* contents = (char*)malloc(1000*sizeof(char));
    int i = 0;
    char character;
    while((character = fgetc(file)) != EOF){
        contents[i++] = character;
    }
    contents[i] = '\0';
    fclose(file);
    return contents;
}
void glfw_errCbck(int code, char *err)
{
    fprintf(stderr, "GLFW Error %d: %s\n", code, err);
}
void gl_printGLError(const uint32_t subject, GLenum pname, char *prefixedMessage)
{
    uint32_t result;
    glad_glGetShaderiv(subject, pname, &result);
    if (!result)
    {
        uint32_t maxLength;
        glad_glGetShaderiv(subject, GL_INFO_LOG_LENGTH, &maxLength);
        char *message = malloc(maxLength * sizeof(char));
        glad_glGetShaderInfoLog(subject, maxLength, &maxLength, message);
        fprintf(stderr, "%s\n%s\n", prefixedMessage, message);
        free(message);
        exit(-1);
    }
}
const uint32_t gl_buildProgram(char *vertPath, char *fragPath)
{
    char *vertShaderSource = readStringFromFile("res/shaders/vert.glsl");
    char *fragShaderSource = readStringFromFile("res/shaders/frag.glsl");
    const uint32_t vShader = glad_glCreateShader(GL_VERTEX_SHADER);
    const uint32_t fShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(vShader, 1, &vertShaderSource, NULL);
    glad_glShaderSource(fShader, 1, &fragShaderSource, NULL);
    glad_glCompileShader(vShader);
    glad_glCompileShader(fShader);
    gl_printGLError(vShader, GL_COMPILE_STATUS, "Vertex shader Error:");
    gl_printGLError(fShader, GL_COMPILE_STATUS, "Fragment shader Error:");
    const uint32_t program = glad_glCreateProgram();
    glad_glAttachShader(program, vShader);
    glad_glAttachShader(program, fShader);
    glad_glLinkProgram(program);
    gl_printGLError(program, GL_LINK_STATUS, "Linking Error:");
    free(vertShaderSource);
    free(fragShaderSource);
    return program;
}