#pragma once
#include "stdint.h"

enum Colors
{
    COLOR_WHITE = 1,
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_RED,
    COLOR_GREEN
};
struct VBLayout
{
    uint32_t attrCount;
    uint32_t attrNames[16];
    uint32_t compCounts[16];
    uint32_t types[16];
    size_t offsets[16];
    uint32_t stride;
    VBLayout *init();
    VBLayout *addAttr(uint32_t attrName, uint32_t compCount, uint32_t type);
};
struct VBO
{
    uint32_t id;
    VBLayout *layout;
    float *data;
    uint32_t vCount;
};
VBO *VBO_init(VBO *vbo, VBLayout *layout);
VBO *VBO_uploadBuffer(VBO *vbo, size_t vCount);

struct Mesh
{
    float *pointer;
    uint32_t vCount;
};

struct MeshArray
{
    VBO *vbo;
    size_t meshCount;
    size_t maxMeshes;
    Mesh **meshes;
};
MeshArray *MeshArray_initMeshArray(MeshArray *ma, VBO *vbo, size_t maxMeshes);
MeshArray *MeshArray_registerMesh(MeshArray *ma, Mesh *mesh);
MeshArray *MeshArray_packVBO(MeshArray *ma);

uint32_t getMeshArrayVCount(MeshArray *arr);

struct BarChart;
MeshArray *makeBasicMeshArray(uint32_t pos_loc, uint32_t color_loc, BarChart* barchart);