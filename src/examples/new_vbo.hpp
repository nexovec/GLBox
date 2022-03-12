#include "examples/examples.hpp"
#include <vector>
#include <cstdint>

struct Vbo_Data_Container : Example_Data_Container
{
    std::vector<float> positions;
    std::vector<float> colors;
    Vbo_Data_Container();
};

struct New_Vbo_Example : Example
{
    Vbo_Data_Container data_containers;
    Vbo_Indices vbo_indices;
    uint32_t program;
    uint32_t position_buffer_binding_point = 0;
    uint32_t color_buffer_binding_point = 1;
    uint32_t pos_loc;
    uint32_t color_loc;
    uint32_t matrix_loc;
    uint32_t vao;
    New_Vbo_Example();
    virtual void update();
};