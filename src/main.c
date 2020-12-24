#define GLFW_INCLUDE_NONE
#include "stdio.h"
#include "stdlib.h"
#include "utils.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

const uint32_t gl_buildProgram(char*,char*);
static void glfw_errCbck(int,char*);
int main(){
    glfwSetErrorCallback(glfw_errCbck);
    if(!glfwInit()){
        return -1;
    }
    GLFWwindow* window =  glfwCreateWindow(800,600,"Hello there",NULL,NULL);
    if(!window){
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    const uint32_t program = gl_buildProgram("res/shaders/vert.glsl","res/shaders/frag.glsl");
    while(glfwWindowShouldClose(window)==GLFW_FALSE){
        glfwPollEvents();
        if(glfwGetKey(window,GLFW_KEY_ESCAPE))glfwSetWindowShouldClose(window,GLFW_TRUE);
        glfwSwapBuffers(window);
        continue;
    }
    return 0;
}
static void glfw_errCbck(int code,char* err){
    fprintf(stderr,"GLFW Error %d: %s\n",code,err);
}
const uint32_t gl_buildProgram(char* vertPath, char* fragPath){
    const char* const vertShaderSource = readStringFromFile("res/shaders/vert.glsl");
    const char* const fragShaderSource = readStringFromFile("res/shaders/frag.glsl");
    const uint32_t vShader = glad_glCreateShader(GL_VERTEX_SHADER);
    const uint32_t fShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(vShader,1,&vertShaderSource,NULL);
    glad_glShaderSource(fShader,1,&fragShaderSource,NULL);
    glad_glCompileShader(vShader);
    glad_glCompileShader(fShader);
    const uint32_t program = glad_glCreateProgram();
    glad_glAttachShader(program, vShader);
    glad_glAttachShader(program, fShader);
    glad_glLinkProgram(program);
    free(vertShaderSource);
    free(fragShaderSource);
    return program;
}