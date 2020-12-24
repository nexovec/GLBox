#define GLFW_INCLUDE_NONE
#include "stdio.h"
#include "stdlib.h"
#include "utils.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

const uint32_t gl_buildProgram(char*,char*);
static void glfw_errCbck(int code,char* err);
int main(){
    //initialize OpenGL
    glfwSetErrorCallback((GLFWerrorfun)glfw_errCbck);
    if(!glfwInit()){
        return -1;
    }
    GLFWwindow* window =  glfwCreateWindow(800,600,"Hello there",NULL,NULL);
    if(!window){
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    const uint32_t program = gl_buildProgram("res/shaders/vert.glsl","res/shaders/frag.glsl");
    // main program loop
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
void printGLError(const uint32_t shader,GLenum pname, char* prefixedMessage);
const uint32_t gl_buildProgram(char* vertPath, char* fragPath){
    char* vertShaderSource = readStringFromFile("res/shaders/vert.glsl");
    char* fragShaderSource = readStringFromFile("res/shaders/frag.glsl");
    const uint32_t vShader = glad_glCreateShader(GL_VERTEX_SHADER);
    const uint32_t fShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(vShader,1,&vertShaderSource,NULL);
    glad_glShaderSource(fShader,1,&fragShaderSource,NULL);
    glad_glCompileShader(vShader);
    glad_glCompileShader(fShader);
    printGLError(vShader,GL_COMPILE_STATUS,"Vertex shader Error:");
    printGLError(fShader,GL_COMPILE_STATUS,"Fragment shader Error:");
    const uint32_t program = glad_glCreateProgram();
    glad_glAttachShader(program, vShader);
    glad_glAttachShader(program, fShader);
    glad_glLinkProgram(program);
    printGLError(program,GL_LINK_STATUS,"Linking Error:");
    free(vertShaderSource);
    free(fragShaderSource);
    return program;
}
void printGLError(const uint32_t shader, GLenum pname, char* prefixedMessage){
    uint32_t result;
    glad_glGetShaderiv(shader,pname,&result);
    if(!result){
        uint32_t maxLength;
        glad_glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&maxLength);
        char* message = malloc(maxLength*sizeof(char));
        glad_glGetShaderInfoLog(shader,maxLength,&maxLength,message);
        fprintf(stderr,"%s\n%s\n",prefixedMessage,message);
        free(message);
        exit(-1);
    }
}