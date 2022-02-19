// #define GLFW_INCLUDE_NONE
#include "pch.hpp"
#include "utils/utils.hpp"
#include "mymath/mymath.hpp"
#include "graphics/graphics.hpp"
#include "examples/examples.hpp"
#include "tests.hpp"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "super_math/super_math.hpp"
static int startup(int argc, char *argv[]);
#ifdef GLBOX_RUN_TESTS
#include "tests.h"
#endif

static int width = 800;
static int height = 600;
static bool running = true;

int main(int argc, char *argv[])
{
#ifdef GLBOX_RUN_TESTS
    runTests();
#endif
    return startup(argc, argv);
}

static int startup(int argc, char *argv[])
{

    glfwInitHint(GLFW_VERSION_MAJOR, 4);
    glfwInitHint(GLFW_VERSION_MINOR, 6);
    if (!glfwInit())
    {
        printf("Couldn't initialize glfw.");
        return -1;
    }
    glfwSetErrorCallback((GLFWerrorfun)glfw_err_callback);
    GLFWwindow *window = glfwCreateWindow(width, height, "GLBox v0.0.1", NULL, NULL);
    if (window == nullptr)
    {
        printf("Couldn't create a window.");
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glClearColor(40.f / 255, 44.f / 255, 40.f / 255, 1.0f);

    Bar_Chart_Example example_1 = Bar_Chart_Example();
    Example *current_example = &example_1;

    while (running)
    {
        glfwPollEvents();
        // code goes here
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        current_example->update();
        glfwSwapBuffers(window);
        if (glfwWindowShouldClose(window) == GLFW_TRUE)
        {
            running = false;
        }
    }
    return 0;
}