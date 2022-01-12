#pragma once
#include "graphing/graphing.hpp"

// BarChart makeSampleBarChart();
// struct Example{
//     // virtual void update() = 0;
//     void update();
// };

struct BarChartExample{
    BarChart barChart;
    MeshArray *ma;
    BarChartExample();
    void update();
};