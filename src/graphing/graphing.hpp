#pragma once
#include "stdint.h"
#include "graphics/graphics.h"
typedef struct BarChart
{
    uint32_t numOfEntries;
    float *entries;
    int *colors;
} BarChart;
Mesh **meshifyChart(BarChart *chart);