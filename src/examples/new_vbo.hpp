#include "examples/examples.hpp"
#include <vector>
#include <cstdint>
struct Example_Data_Container
{
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<float> elements;
    Example_Data_Container();
};
struct Vbo_Indices
{
    uint32_t positions;
    uint32_t colors;
    uint32_t elements;
};

struct New_Vbo_Example : Example
{
    Example_Data_Container data_containers;
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