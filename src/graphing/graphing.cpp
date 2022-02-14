#include "pch.hpp"
#include "graphing.hpp"
#include "graphics/graphics.hpp"
#include "graphics/primitives.hpp"
#include "utils/utils.hpp"
#include "stdlib.h"

Mesh **Bar_Chart::meshify_chart()
{
    // TODO: abstract these integers
    int x = 100;
    int y = 500;
    int entryWidth = 19;
    int spacingWidth = 5;
    float scale = 1.0f;
    // FIXME: leaks
    Mesh **meshes = (Mesh **)malloc((1 + this->num_of_entries) * sizeof(Mesh *));
    for (int i = 0; i < (int)this->num_of_entries; i++)
    {
        // FIXME: naming
        int yCoord = (int)(this->entries[i] * scale);
        Vec3f first = {(float)x + spacingWidth + i * (spacingWidth + entryWidth), (float)y - yCoord, 0};
        Vec3f second = {(float)entryWidth, (float)yCoord, 0};
        meshes[i] = make_quad_mesh(
            &first,
            &second,
            COLOR_BLUE);
    }
    Vec3f first = {(float)x, (float)y, 0};
    Vec3f second = {(float)(this->num_of_entries + 1) * spacingWidth + this->num_of_entries * entryWidth, entryWidth * 1.69f, 0};
    meshes[this->num_of_entries] = make_quad_mesh(
        &first,
        &second,
        COLOR_BLACK);
    return meshes;
}