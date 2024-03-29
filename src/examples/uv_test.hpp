#pragma once
#include "examples/examples.hpp"
#include <cstdint>
#include <vector>

struct Uv_Test_Data_Container
{
  std::vector<float> positions;
  std::vector<float> tex_coords;
  std::vector<uint32_t> elements;
  Uv_Test_Data_Container();
};

struct Uv_Test_Example : Example
{
  Uv_Test_Data_Container data_containers;
  Vbo_Indices_Uv attrib_buffer_indices;
  uint32_t program;
  uint32_t position_buffer_binding_point = 0;
  uint32_t tex_coords_binding_point = 1;
  uint32_t texture_id;
  uint32_t pos_loc;
  uint32_t tex_coord_loc;
  uint32_t matrix_loc;
  uint32_t vao;
  Uv_Test_Example();
  virtual void update();
};