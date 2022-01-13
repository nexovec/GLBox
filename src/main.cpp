#define GLFW_INCLUDE_NONE
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

#include "super_math.hpp"
static int startup(const uint32_t width, const uint32_t height);
#ifdef GLBOX_RUN_TESTS
#include "tests.h"
#endif

int main()
{
#ifdef GLBOX_RUN_TESTS
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
    GLFWwindow *window = glfwCreateWindow(width, height, "GLBox 0.0.1 dev", NULL, NULL);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow *menuWindow = glfwCreateWindow(300, height, "Menu", NULL, NULL);
    if (!(window && menuWindow))
        return -1;
    const GLFWvidmode *v = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int centerW = v->width / 2 - width / 2, centerH = v->height / 2 - height / 2;
    glfwSetWindowPos(window, centerW, centerH);
    glfwSetWindowPos(menuWindow, centerW - 50 - 300, centerH - 10);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // SECTION: math
    //const float ratio = 4 / 3;
    //Mat4_f translation, rot;
    // Mat4f ortho, translation, rot, MVP;
    // Mat4f_ortho(&ortho, 600.f * ratio, 0.f, 0.f, 600.f, -1.0f, 1.0f);
    // Mat4f_translation(&translation, 0.f, 0.f, 0.f);
    // auto ortho = Mat4_f::ortho_projection_matrix(0.f, 600.f * ratio, 0.f, 600.f, 1.0f, -1.0f);
    // ! FIXME:
    // RESEARCH: why the f does the following not work?
    // Mat4_f ortho = Mat4_f::perspective_projection_matrix(80.f, (GLfloat)width / (GLfloat)height, 0.f, 1000.0f);
    // glm::mat4 ortho = glm::perspective(80.f, (GLfloat)width / (GLfloat)height, 0.f, 1000.0f);
    // glm::mat4 ortho = glm::ortho(0.f, (GLfloat)width, (GLfloat)height, 0.f, 0.f, 1000.f);
    // RESEARCH: why the f does the following not work?
    // glm::mat4 ortho = glm::ortho(0, 800, 600, 0, 0, 1000);

    // SECTION: GPU init
    // const uint32_t program = gl_buildProgram((char *)"res/shaders/vert.glsl", (char *)"res/shaders/frag.glsl");
    // // TODO: error handle shader runtime
    // glad_glUseProgram(program);
    // const int32_t pos_loc = glad_glGetAttribLocation(program, "pos");
    // const int32_t color_loc = glad_glGetAttribLocation(program, "color");
    // const int32_t globT_loc = glad_glGetUniformLocation(program, "globT");

    // SECTION: data instantiation
    // BarChart barchart = makeSampleBarChart();
    // MeshArray *ma = makeBasicMeshArray(pos_loc, color_loc, &barchart);

    // TODO: use a constructor
    BarChartExample currentExample;

    // SECTION: main program loop
    glad_glClearColor(40.f / 255, 44.f / 255, 40.f / 255, 1.0f);
    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        glfwPollEvents();
        // canvas screen
        glfwMakeContextCurrent(window);
        glad_glClear(GL_COLOR_BUFFER_BIT);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        // rot = *Mat4f_rotation(&rot, 0.f, 0.f, (float)glfwGetTime());
        // rot = *Mat4f_identity(&rot);
        // MVP = *Mat4f_multiply(&MVP, Mat4f_multiply(&MVP, &ortho, &translation), &rot);
        // rot = Mat4_f::rotation_matrix(0.f, 0.f, (float)glfwGetTime());
        // MVP = ortho * (Mat4_f::unit_matrix() * (1/2)) *rot;
        // glm::mat4 MVP = ortho;
        //glad_glUniformMatrix4fv(globT_loc, 1, GL_FALSE, MVP.row_aligned_elems);
        // glad_glUniformMatrix4fv(globT_loc, 1, GL_FALSE, glm::value_ptr(MVP));
        currentExample.update();
        glfwSwapBuffers(window);
        // menu screen
        glfwMakeContextCurrent(menuWindow);
        glad_glClearColor(40.f / 255, 44.f / 255, 40.f / 255, 1.0f);
        if (glfwGetKey(menuWindow, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        glad_glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(menuWindow);
        continue;
    }
    return 0;
}
