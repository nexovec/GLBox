#pragma once
#include "examples/examples.hpp"
#include <vector>
#include <cstdint>

struct DSA_Uv_Data_Container : Example_Data_Container
{
    std::vector<float> positions;
    std::vector<float> tex_coords;
    std::vector<uint32_t> elements;
    DSA_Uv_Data_Container();
};

struct DSA_Uv_Example : Example
{
    DSA_Uv_Data_Container data_containers;
    Vbo_Indices_Uv attrib_buffer_indices;
    uint32_t program;
    uint32_t position_buffer_binding_point = 0;
    uint32_t tex_coords_buffer_binding_point = 1;
    uint32_t pos_loc;
    uint32_t tex_coords_loc;
    uint32_t texture_id;
    uint32_t matrix_loc;
    uint32_t vao;
    DSA_Uv_Example();
    virtual void update();
};