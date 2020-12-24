#define GLFW_INCLUDE_NONE
#include "stdio.h"
#include "stdlib.h"
#include "utils.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

uint32_t gl_buildProgram(char*,char*);
void glfw_errCbck(int,char*);
int main(){
    glfwSetErrorCallback(glfw_errCbck);
    if(!glfwInit()){
        return -1;
    }
    GLFWwindow* window =  glfwCreateWindow(800,600,"Hello there",NULL,NULL);
    if(!window){
        return -1;
    }
    uint32_t program = gl_buildProgram("res/shaders/vert.glsl","res/shaders/frag.glsl");
    printf("bye bye");
    while(glfwWindowShouldClose(window)==GLFW_FALSE){
        glfwPollEvents();
        if(glfwGetKey(window,GLFW_KEY_ESCAPE))glfwSetWindowShouldClose(window,GLFW_TRUE);
        glfwSwapBuffers(window);
        continue;
    }
    return 0;
}
void glfw_errCbck(int code,char* err){
    fprintf(stderr,"GLFW Error %d: %s\n",code,err);
}
uint32_t gl_buildProgram(char* vertPath, char* fragPath){
    char* vertShaderSource = readStringFromFile("res/shaders/vert.glsl");
    char* fragShaderSource = readStringFromFile("res/shaders/frag.glsl");

    free(vertShaderSource);
    free(fragShaderSource);
    return 0;
}