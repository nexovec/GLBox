#include "stdint.h"
#include "mymath/mymath.h"
#include "graphics/graphics.h"
typedef struct BarChart
{
    uint32_t numOfVertices;
    Vec3f *positions;
    Vec3f *colors;
} BarChart;
MeshArray *meshifyChart(BarChart *chart);

// temporary
BarChart *makeSampleBarChart();