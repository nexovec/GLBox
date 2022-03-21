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
struct Vbo_Indices
{
    uint32_t positions;
    uint32_t colors;
    uint32_t elements;
};