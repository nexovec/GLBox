#pragma once
#include "stdint.h"
#include "graphics/graphics.hpp"
struct BarChart
{
    uint32_t numOfEntries;
    float *entries;
    int *colors;
};
Mesh ** meshifyChart(BarChart *chart);