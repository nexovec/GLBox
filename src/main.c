#include "stdio.h"
#include "GLFW/glfw3.h"
int main(){
    printf("Hello world!");
    if(!glfwInit()){
        return -1;
    }
    GLFWwindow* window =  glfwCreateWindow(800,600,"Hello there",NULL,NULL);
    if(!window){
        return -1;
    }
    while(glfwWindowShouldClose(window)==GL_FALSE){
        glfwPollEvents();
        glfwSwapBuffers(window);
        continue;
    }
}