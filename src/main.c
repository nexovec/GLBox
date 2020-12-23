#define GLFW_INCLUDE_NONE
#include "stdio.h"
#include "stdlib.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

uint32_t gl_buildProgram(char*,char*);
char* readStringFromFile(char*);
int main(){
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
uint32_t gl_buildProgram(char* vertPath, char* fragPath){
    char* vertShaderSource = readStringFromFile("res/shaders/vert.glsl");
    char* fragShaderSource = readStringFromFile("res/shaders/frag.glsl");
    free(vertShaderSource);
    free(fragShaderSource);
    return 0;
}
char* readStringFromFile(char* path){
    FILE* file = fopen(path,"r");
    char* contents = (char*)malloc(1000*sizeof(char));
    int i = 0;
    char character;
    while((character = fgetc(file)) != EOF){
        contents[i++] = character;
    }
    contents[i] = '\0';
    printf("%s",contents);// ::DEBUG
    fclose(file);
    return contents;
}