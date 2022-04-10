#pragma once
#include "examples/examples.hpp"
#include <vector>
#include <cstdint>

struct OBJ_Loader_Data_Container
{
    std::vector<float> positions;
    std::vector<float> tex_coords;
    std::vector<uint32_t> elements;
    OBJ_Loader_Data_Container();
};

struct OBJ_Loader_Example : Example
{
    OBJ_Loader_Data_Container data_containers;
    Vbo_Indices_Uv attrib_buffer_indices;
    uint32_t program;
    uint32_t position_buffer_binding_point = 0;
    uint32_t tex_coords_buffer_binding_point = 1;
    uint32_t pos_loc;
    uint32_t tex_coords_loc;
    uint32_t texture_id;
    uint32_t matrix_loc;
    uint32_t vao;
    OBJ_Loader_Example();
    virtual void update();
};