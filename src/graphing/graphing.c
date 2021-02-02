#include "graphing.h"
#include "graphics/graphics.h"
#include "graphics/primitives.h"
#include "utils/utils.h"
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
    Mesh **meshes = malloc((1 + chart->numOfEntries) * sizeof(Mesh *));
    for (int i = 0; i < (int)chart->numOfEntries; i++)
    {
        int yCoord = (int)(chart->entries[i] * scale);
        meshes[i] = makeQuadMesh(
            &(Vec3f){(float)x + spacingWidth + i * (spacingWidth + entryWidth), (float)y - yCoord, 0},
            &(Vec3f){(float)entryWidth, (float)yCoord, 0},
            COLOR_BLUE);
    }
    meshes[chart->numOfEntries] = makeQuadMesh(
        &(Vec3f){(float)x, (float)y, 0},
        &(Vec3f){(float)(chart->numOfEntries + 1) * spacingWidth + chart->numOfEntries * entryWidth, entryWidth * 1.69f, 0},
        COLOR_BLACK);
    return meshes;
}