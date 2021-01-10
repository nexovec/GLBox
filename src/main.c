#define GLFW_INCLUDE_NONE
#include "utils/utils.h"
#include "mymath/mymath.h"
#include "graphics/graphics.h"
#include "tests.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
static int startup();

int main()
{
#ifdef GLE_RUN_TESTS
#include "tests.h"
    runTests();
#endif
    return startup();
}
static int startup()
{
    // SECTION: initialize OpenGL
    glfwSetErrorCallback((GLFWerrorfun)glfw_errCbck);
    if (!glfwInit())
    {
        return -1;
    }
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello there", NULL, NULL);
    GLFWwindow *menuWindow = glfwCreateWindow(300, 600, "Menu window", NULL, NULL);
    if (!(window && menuWindow))
    {
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // SECTION: defining data
    float positionsf[18] = {
        400.f, 200.f, 0.0f,
        1.0, 0.0, 0.0, /* Red */
        500.f, 300.f, 0.0f,
        0.0, 1.0, 0.0, /* Green */
        0.0f, 400.f, 0.0f,
        0.0, 0.0, 1.0}; /* Blue */
    // SECTION: math
    const float ratio = 4 / 3;
    Mat4f ortho, translation, rot, MVP;
    Mat4f_ortho(&ortho, 800.f, 0.f, 0.f, 600.f, -1.0f, 1.0f);
    Mat4f_translation(&translation, 0.5f, 0.3f, 0.f);
    // SECTION: GPU data transfer
    const uint32_t program = gl_buildProgram("res/shaders/vert.glsl", "res/shaders/frag.glsl");
    // TODO: error handle shader runtime
    glad_glUseProgram(program);
    const int32_t pos_loc = glad_glGetAttribLocation(program, "pos");
    const int32_t color_loc = glad_glGetAttribLocation(program, "color");
    const int32_t globT_loc = glad_glGetUniformLocation(program, "globT");

    // uint32_t vao;
    // glad_glGenVertexArrays(1, &vao);
    // glad_glBindVertexArray(vao);
    // VBLayout vbl;
    // VBLayout_init(&vbl);
    // VBLayout_addAttr(&vbl, pos_loc, 3, GL_FLOAT);
    // VBLayout_addAttr(&vbl, color_loc, 3, GL_FLOAT);
    // VBO vbo;
    // vbo.data = positionsf;
    // VBO_init(&vbo, &vbl, 3);

    // temporary
    MeshArray *ma = makeBasicMeshArray(pos_loc,color_loc);
    // SECTION: main program loop
    glad_glClearColor(0.3f, 0.7f, 0.3f, 1.0f);
    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        glfwPollEvents();
        // canvas screen
        glfwMakeContextCurrent(window);
        glad_glClear(GL_COLOR_BUFFER_BIT);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        rot = *Mat4f_rotation(&rot, 0.f, 0.f, (float)glfwGetTime());
        MVP = *Mat4f_multiply(&MVP, Mat4f_multiply(&MVP, &ortho, &translation), &rot);
        glad_glUniformMatrix4fv(globT_loc, 1, GL_FALSE, MVP.members);
        glad_glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        // menu screen
        glfwMakeContextCurrent(menuWindow);
        glad_glClearColor(0.3f, 0.7f, 0.3f, 1.0f);
        if (glfwGetKey(menuWindow, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        glad_glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(menuWindow);
        continue;
    }
    return 0;
}
