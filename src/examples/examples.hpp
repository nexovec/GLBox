#pragma once
#include "graphing/graphing.hpp"
#include <iostream>

struct BarChartExample
{
    BarChart barChart;
    MeshArray ma;
    BarChartExample();
    void update();
};