#include "pch.hpp"
#include "stdlib.h"
#include "examples/examples.hpp"
#include "graphing/graphing.hpp"
#include "algorithms/sequences.hpp"
#include "utils/utils.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <string>
#define ENTRIES 10
static Bar_Chart make_sample_bar_chart()
{
    Bar_Chart res;
    res.num_of_entries = ENTRIES;
    res.colors = (int *)malloc((res.num_of_entries + 1) * sizeof(int));
    uint32_t entries[ENTRIES];
    // rangeIntSequence(entries,res.num_of_entries,1,1);
    randIntSequence((int32_t *)entries, res.num_of_entries, 1, 300);
    // FIXME: leaks
    res.entries = (float *)malloc(res.num_of_entries * sizeof(float));
    for (uint32_t i = 0; i < res.num_of_entries; i++)
        res.entries[i] = (float)entries[i];
    // print_float_arr(res.entries, ENTRIES);
    return res;
}

Bar_Chart_Example::Bar_Chart_Example()
{
    int width = 800;
    int height = 600;
    const uint32_t program = gl_build_program(PATH_TO_VEREX_SHADER, PATH_TO_FRAGMENT_SHADER);
    // TODO: error handle shader runtime
    glad_glUseProgram(program);

    const int32_t pos_loc = glad_glGetAttribLocation(program, "pos");
    const int32_t color_loc = glad_glGetAttribLocation(program, "color");
    const int32_t globT_loc = glad_glGetUniformLocation(program, "globT");
    glm::mat4 ortho = glm::ortho(0.f, (GLfloat)width, (GLfloat)height, 0.f, 0.f, 1000.f);
    glad_glUniformMatrix4fv(globT_loc, 1, GL_FALSE, glm::value_ptr(ortho));
    // TODO: use data
    barChart = make_sample_bar_chart();
    ma = Mesh_Array::make_basic_mesh_array(pos_loc, color_loc, &barChart);
}
void Bar_Chart_Example::update()
{
    // TODO:
    glad_glDrawArrays(GL_TRIANGLES, 0, this->ma.vbo->v_count);
}