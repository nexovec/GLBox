#include "examples/examples.hpp"
#include <cstdint>
struct Example_Data_Container
{
    float *positions;
    float *colors;
    Example_Data_Container();
    ~Example_Data_Container();
};
struct Vbo_Indices
{
    uint32_t positions;
    uint32_t colors;
};

struct New_Vbo_Example : Example
{
    Example_Data_Container data_containers;
    Vbo_Indices vbo_indices;
    uint32_t program;
    uint32_t position_buffer_binding_point;
    uint32_t color_buffer_binding_point;
    uint32_t pos_loc;
    uint32_t color_loc;
    uint32_t matrix_loc;
    uint32_t vao;
    New_Vbo_Example();
    virtual void update();
};