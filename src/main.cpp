// #define GLFW_INCLUDE_NONE
#include "pch.hpp"
#include "utils/utils.hpp"
#include "mymath/mymath.hpp"
#include "graphics/graphics.hpp"
#include "examples/examples.hpp"
#include "examples/new_vbo.hpp"
#include "examples/new_ebo.hpp"
#include "examples/uv_test.hpp"
#include "examples/dsa_example.hpp"
#include "examples/dsa_uv.hpp"
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
    return pressed_key_map.contains(key);
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
    if (!glfwInit())
    {
        printf("Couldn't initialize glfw.");
        return -1;
    }
    struct glfwWindowCreateInfo
    {
        bool maximize;
        bool decorate;
    };
    glfwWindowCreateInfo createInfo = {false, true};
    glfwSetErrorCallback((GLFWerrorfun)glfw_err_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, createInfo.maximize);
    glfwWindowHint(GLFW_DECORATED, createInfo.decorate);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "GLBox v0.0.1", NULL, NULL);
    if (window == nullptr)
    {
        printf("Couldn't create a window.");
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // std::cout << glGetString(GL_VERSION) << std::endl;
    // std::cout << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl;
    glClearColor(40.f / 255, 44.f / 255, 40.f / 255, 1.0f);

    // Bar_Chart_Example example_1 = Bar_Chart_Example();
    // Example *current_example = &example_1;

    std::unique_ptr<New_Vbo_Example> new_vbo_rendering_example = std::make_unique<New_Vbo_Example>();
    std::unique_ptr<New_Ebo_Example> new_ebo_rendering_example = std::make_unique<New_Ebo_Example>();
    std::unique_ptr<DSA_Test_Example> DSA_example = std::make_unique<DSA_Test_Example>();
    std::unique_ptr<Uv_Test_Example> uv_test_example = std::make_unique<Uv_Test_Example>();
    std::unique_ptr<DSA_Uv_Example> DSA_uv_example = std::make_unique<DSA_Uv_Example>();

    Example *current_example;
    current_example = new_vbo_rendering_example.get();
    current_example = new_ebo_rendering_example.get();
    current_example = DSA_example.get();
    current_example = uv_test_example.get();
    current_example = DSA_uv_example.get();

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