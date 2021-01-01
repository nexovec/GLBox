#include "stdint.h"
#include "mymath/mymath.h"
typedef struct BarChart
{
    uint32_t numOfVertices;
    Vec3f *positions;
    Vec3f *colors;
} BarChart;