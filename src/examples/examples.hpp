#pragma once
#include "graphing/graphing.hpp"
#include <iostream>

struct Bar_Chart_Example
{
    Bar_Chart barChart;
    Mesh_Array ma;
    Bar_Chart_Example();
    void update();
};