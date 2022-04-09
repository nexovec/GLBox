#pragma once
#include "graphing/graphing.hpp"
#include <iostream>
#include <vector>
struct Example
{
    Example(){};
    virtual void update() = 0;
};

struct Example_Data_Container
{
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<float> elements;
};
struct Basic_Shader_Vbo_Indices
{
    uint32_t positions;
    uint32_t colors;
    uint32_t elements;
};

struct Vbo_Indices_Uv
{
    uint32_t positions;
    uint32_t elements;
    uint32_t tex_coords;
};

static void populate_unit_cube_vertex_positions(std::vector<float> &vec)
{
    float data[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f};
    for (const float &thing : data)
    {
        vec.push_back(thing);
    }
}