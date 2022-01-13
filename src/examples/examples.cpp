#include "stdlib.h"
#include "examples/examples.hpp"
#include "graphing/graphing.hpp"
#include "algorithms/sequences.hpp"
#include "utils/utils.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <string>
#define ENTRIES 10
BarChart makeSampleBarChart()
{
    BarChart res;
    res.numOfEntries = ENTRIES;
    res.colors = (int *)malloc((res.numOfEntries + 1) * sizeof(int));
    uint32_t entries[ENTRIES];
    // rangeIntSequence(entries,res.numOfEntries,1,1);
    randIntSequence((int32_t *)entries, res.numOfEntries, 1, 300);
    res.entries = (float *)malloc(res.numOfEntries * sizeof(float));
    for (uint32_t i = 0; i < res.numOfEntries; i++)
        res.entries[i] = (float)entries[i];
    printFloatArr(res.entries, ENTRIES);
    return res;
}

BarChartExample::BarChartExample(){
    int width = 800;
    int height = 600;
    const uint32_t program = gl_buildProgram("res/shaders/vert.glsl","res/shaders/frag.glsl");
    // TODO: error handle shader runtime
    glad_glUseProgram(program);

    const int32_t pos_loc = glad_glGetAttribLocation(program, "pos");
    const int32_t color_loc = glad_glGetAttribLocation(program, "color");
    const int32_t globT_loc = glad_glGetUniformLocation(program, "globT");
    glm::mat4 ortho = glm::ortho(0.f, (GLfloat)width, (GLfloat)height, 0.f, 0.f, 1000.f);
    glad_glUniformMatrix4fv(globT_loc, 1, GL_FALSE, glm::value_ptr(ortho));
    // TODO: use data
    barChart = makeSampleBarChart();
    ma = makeBasicMeshArray(pos_loc, color_loc, &barChart);
}
void BarChartExample::update(){
    // TODO:
    glad_glDrawArrays(GL_TRIANGLES, 0, this->ma->vbo->vCount);
}