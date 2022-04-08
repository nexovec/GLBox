#pragma once
#include "examples/examples.hpp"
#include <vector>
#include <cstdint>

struct DSA_Test_Data_Container : Example_Data_Container
{
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<uint32_t> elements;
    DSA_Test_Data_Container();
};

struct DSA_Test_Example : Example
{
    DSA_Test_Data_Container data_containers;
    Vbo_Indices attrib_buffer_indices;
    uint32_t program;
    uint32_t position_buffer_binding_point = 0;
    uint32_t color_buffer_binding_point = 1;
    uint32_t pos_loc;
    uint32_t color_loc;
    uint32_t matrix_loc;
    uint32_t vao;
    DSA_Test_Example();
    virtual void update();
};