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
#ifdef GLBOX_RUN_TESTS
#include "tests.h"
    runTests();
#endif
    return startup(800, 600);
}
static int startup(const uint32_t width, const uint32_t height)
{
    // SECTION: initialize OpenGL
    glfwSetErrorCallback((GLFWerrorfun)glfw_errCbck);
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(width, height, "Hello there", NULL, NULL);
    GLFWwindow *menuWindow = glfwCreateWindow(300, height, "Menu window", NULL, NULL);
    if (!(window && menuWindow))
        return -1;
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // SECTION: math
    const float ratio = 4 / 3;
    Mat4f ortho, translation, rot, MVP;
    Mat4f_ortho(&ortho, 600.f * ratio, 0.f, 0.f, 600.f, -1.0f, 1.0f);
    Mat4f_translation(&translation, 0.f, 0.f, 0.f);

    // SECTION: GPU data transfer
    const uint32_t program = gl_buildProgram("res/shaders/vert.glsl", "res/shaders/frag.glsl");
    // TODO: error handle shader runtime
    glad_glUseProgram(program);
    const int32_t pos_loc = glad_glGetAttribLocation(program, "pos");
    const int32_t color_loc = glad_glGetAttribLocation(program, "color");
    const int32_t globT_loc = glad_glGetUniformLocation(program, "globT");

    // temporary
    printf("initializing MeshArray");
    MeshArray *ma = makeBasicMeshArray(pos_loc, color_loc);
    printf("Mesh array created!");

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
        // rot = *Mat4f_rotation(&rot, 0.f, 0.f, (float)glfwGetTime());
        rot = *Mat4f_identity(&rot);
        MVP = *Mat4f_multiply(&MVP, Mat4f_multiply(&MVP, &ortho, &translation), &rot);
        glad_glUniformMatrix4fv(globT_loc, 1, GL_FALSE, MVP.members);
        glad_glDrawArrays(GL_TRIANGLES, 0, ma->vbo->vCount);
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
