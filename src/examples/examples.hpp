#pragma once
#include "graphing/graphing.hpp"
#include <iostream>
struct Example
{
    Example(){};
    virtual void update() = 0;
};

struct Bar_Chart_Example : Example
{
    Bar_Chart barChart;
    Mesh_Array ma;
    Bar_Chart_Example();
    virtual void update();
};