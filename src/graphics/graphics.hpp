#pragma once
#include "stdint.h"

enum Colors
{
    COLOR_WHITE = 1,
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_RED,
    COLOR_GREEN
};
struct VB_Layout
{
    uint32_t attr_count;
    uint32_t attr_names[16];
    uint32_t comp_counts[16];
    uint32_t types[16];
    size_t offsets[16];
    uint32_t stride;
    VB_Layout();
    VB_Layout *add_attr(uint32_t attrName, uint32_t compCount, uint32_t type);
};
struct VBO
{
    uint32_t id;
    VB_Layout *layout;
    float *data;
    uint32_t v_count;
    VBO(VB_Layout *layout);
    void upload_buffer();
};

struct Mesh
{
    float *pointer;
    uint32_t v_count;
};

struct Bar_Chart;
struct Mesh_Array
{
    VBO *vbo;
    size_t mesh_count;
    size_t max_meshes;
    Mesh **meshes;
    Mesh_Array();
    Mesh_Array(Mesh_Array *other);
    Mesh_Array(VBO *vbo, size_t max_meshes);
    ~Mesh_Array();
    void register_mesh(Mesh *mesh);
    void pack_VBO();
    uint32_t get_vertex_count();
    static Mesh_Array make_basic_mesh_array(uint32_t pos_loc, uint32_t color_loc, Bar_Chart *barchart);
};