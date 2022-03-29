// #define GLFW_INCLUDE_NONE
#include "pch.hpp"
#include "utils/utils.hpp"
#include "mymath/mymath.hpp"
#include "graphics/graphics.hpp"
#include "examples/examples.hpp"
#include "examples/new_vbo.hpp"
#include "examples/new_ebo.hpp"
#include "examples/uv_test.hpp"
#include "tests.hpp"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <memory>
#include <glm/ext.hpp>
#include <unordered_map>

#include "super_math/super_math.hpp"
static int startup(int argc, char *argv[]);
#ifdef GLBOX_RUN_TESTS
#include "tests.h"
#endif

static bool running = true;

int main(int argc, char *argv[])
{
#ifdef GLBOX_RUN_TESTS
    runTests();
#endif
    return startup(argc, argv);
}

static std::unordered_map<int, bool> pressed_key_map;

bool get_key_state(int key)
{
    if (pressed_key_map.contains(key))
        return true;
    return false;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
        std::cout << key << "\t|\t" << glfwGetKeyScancode(key) << "\t|\t" << (int)'E' << std::endl;

    switch (action)
    {
    case GLFW_RELEASE:
        if (pressed_key_map.contains(key))
        {
            pressed_key_map.erase(key);
        }
        break;
    default:
        pressed_key_map.insert_or_assign(key, true);
        break;
    }
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
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "GLBox v0.0.1", NULL, NULL);
    if (window == nullptr)
    {
        printf("Couldn't create a window.");
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glClearColor(40.f / 255, 44.f / 255, 40.f / 255, 1.0f);

    // Bar_Chart_Example example_1 = Bar_Chart_Example();
    // Example *current_example = &example_1;

    std::unique_ptr<New_Vbo_Example> new_vbo_rendering_example = std::make_unique<New_Vbo_Example>();
    std::unique_ptr<New_Ebo_Example> new_ebo_rendering_example = std::make_unique<New_Ebo_Example>();
    std::unique_ptr<Uv_Test_Example> uv_test_example = std::make_unique<Uv_Test_Example>();

    Example *current_example;
    current_example = new_vbo_rendering_example.get();
    current_example = new_ebo_rendering_example.get();
    current_example = uv_test_example.get();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
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