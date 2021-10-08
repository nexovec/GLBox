#include "graphing.hpp"
#include "graphics/graphics.hpp"
#include "graphics/primitives.hpp"
#include "utils/utils.hpp"
#include "stdlib.h"

Mesh **meshifyChart(BarChart *chart)
{
    // TODO: abstract these integers
    int x = 100;
    int y = 500;
    int entryWidth = 19;
    int spacingWidth = 5;
    float scale = 1.0f;
    // FIXME: leaks
    Mesh **meshes = (Mesh**)malloc((1 + chart->numOfEntries) * sizeof(Mesh *));
    for (int i = 0; i < (int)chart->numOfEntries; i++)
    {
        // FIXME: naming
        int yCoord = (int)(chart->entries[i] * scale);
        Vec3f first = { (float)x + spacingWidth + i * (spacingWidth + entryWidth), (float)y - yCoord, 0 };
        Vec3f second = { (float)entryWidth, (float)yCoord, 0 };
        meshes[i] = makeQuadMesh(
            &first,
            &second,
            COLOR_BLUE);
    }
    Vec3f first = { (float)x, (float)y, 0 };
    Vec3f second = { (float)(chart->numOfEntries + 1) * spacingWidth + chart->numOfEntries * entryWidth, entryWidth * 1.69f, 0 };
    meshes[chart->numOfEntries] = makeQuadMesh(
        &first,
        &second,
        COLOR_BLACK);
    return meshes;
}