#pragma once
#include "stdint.h"
#include "graphics/graphics.hpp"
struct Bar_Chart
{
    uint32_t num_of_entries;
    float *entries;
    int *colors;
    Mesh **meshify_chart();
};