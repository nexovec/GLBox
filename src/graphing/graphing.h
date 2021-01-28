#pragma once
#include "stdint.h"
#include "mymath/mymath.h"
#include "graphics/graphics.h"
typedef struct BarChart
{
    uint32_t numOfEntries;
    float *entries;
    int *colors;
} BarChart;
Mesh **meshifyChart(BarChart *chart);

// temporary
BarChart makeSampleBarChart();