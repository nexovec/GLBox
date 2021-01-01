#define GLFW_INCLUDE_NONE
#include "utils/utils.h"
#include "mymath/mymath.h"
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
    if (!window)
    {
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // SECTION: defining data
    float positionsf[18] = {
        -0.6f, -0.4f, 0.0f,
        1.0, 0.0, 0.0, /* Red */
        0.6f, -0.4f, 0.0f,
        0.0, 1.0, 0.0, /* Green */
        0.0f, 0.6f, 0.0f,
        0.0, 0.0, 1.0}; /* Blue */
    // Vec3f positions[3];
    // Vec3f colors[4];
    // Vec3f_fromFloatArr(positions, (float *)positionsf, 3);
    // Vec3f_fromFloatArr(colors, (float *)colorsf, 4);
    // SECTION: GPU data transfer
    const uint32_t program = gl_buildProgram("res/shaders/vert.glsl", "res/shaders/frag.glsl");
    // TODO: error handle shader runtime
    glad_glUseProgram(program);
    const int32_t pos_loc = glad_glGetAttribLocation(program, "pos");
    const int32_t color_loc = glad_glGetAttribLocation(program, "color");
    const int32_t globT_loc = glad_glGetUniformLocation(program, "globT");

    const float ratio = 4 / 3;
    Mat4f ortho, translation, rot, MVP;
    Mat4f_ortho(&ortho, ratio, -ratio, 1.0f, -1.0f, -1.0f, 1.0f);
    Mat4f_translation(&translation, 0.5f, 0.3f, 0.f);

    uint32_t vbo;
    glad_glGenBuffers(1, &vbo);
    uint32_t vao;

    glad_glGenVertexArrays(1, &vao);
    glad_glBindVertexArray(vao);

    glad_glEnableVertexAttribArray(pos_loc);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(positionsf), positionsf, GL_STATIC_DRAW);
    glad_glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    glad_glEnableVertexAttribArray(color_loc);
    // glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glad_glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors, GL_STATIC_DRAW);
    glad_glVertexAttribPointer(color_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *)(sizeof(float) * 3));
    // SECTION: main program loop
    glad_glClearColor(0.3f, 0.7f, 0.3f, 1.0f);
    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        glfwPollEvents();
        glad_glClear(GL_COLOR_BUFFER_BIT);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        Mat4f_rotation(&rot, 0.f, 0.f, (float)glfwGetTime());
        Mat4f_multiply(&MVP, Mat4f_multiply(&MVP, &ortho, &translation), &rot);
        glad_glUniformMatrix4fv(globT_loc, 1, GL_FALSE, MVP.members);
        glad_glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        continue;
    }
    return 0;
}
