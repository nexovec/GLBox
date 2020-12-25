#define GLFW_INCLUDE_NONE
#include "stdio.h"
#include "stdlib.h"
#include "utils.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

const uint32_t gl_buildProgram(char*,char*);
static void glfw_errCbck(int code,char* err);
static void runTests();
static int startup();
void printGLError(const uint32_t shader,GLenum pname, char* prefixedMessage);

int main(){
#ifdef RUN_TESTS
    runTests();
#endif
    return startup();
}
static int startup(){
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
    // defining data
    const float positions[] = {-0.6f, -0.4f, 0.6f, -0.4f, 0.f,  0.6f};
    const float colors[4][3] = {
    {  1.0,  0.0,  0.0  }, /* Red */
    {  0.0,  1.0,  0.0  }, /* Green */
    {  0.0,  0.0,  1.0  }}; /* Blue */
    // GPU data transfer
    const uint32_t program = gl_buildProgram("res/shaders/vert.glsl","res/shaders/frag.glsl");
    const int32_t pos_loc = glad_glGetAttribLocation(program,"pos"); // TODO: Error handling for the entire block
    const int32_t color_loc = glad_glGetAttribLocation(program,"color");

    uint32_t vbo[2];
    glad_glGenBuffers(2,&vbo);
    uint32_t vao;
    glad_glGenVertexArrays(1,&vao);
    glad_glBindVertexArray(vao);

    glad_glEnableVertexAttribArray(pos_loc);
    glad_glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
    glad_glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW);
    glad_glVertexAttribPointer(pos_loc,2,GL_FLOAT,GL_FALSE,2*sizeof(float),0);

    glad_glEnableVertexAttribArray(color_loc);
    glad_glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
    glad_glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);
    glad_glVertexAttribPointer(color_loc,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    // main program loop
    glad_glClearColor(0.3f,0.7f,0.3f,1.0f);
    while(glfwWindowShouldClose(window)==GLFW_FALSE){
        glfwPollEvents();
        glad_glClear(GL_COLOR_BUFFER_BIT);
        if(glfwGetKey(window,GLFW_KEY_ESCAPE))glfwSetWindowShouldClose(window,GLFW_TRUE);
        glad_glUseProgram(program);
        glad_glDrawArrays(GL_TRIANGLES,0,3);
        glfwSwapBuffers(window);
        continue;
    }
    return 0;

}
static void runTests(){
    return;
}
static void glfw_errCbck(int code,char* err){
    fprintf(stderr,"GLFW Error %d: %s\n",code,err);
}
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