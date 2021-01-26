#pragma once
#include "stdint.h"
typedef struct VBLayout
{
    uint32_t attrCount;
    uint32_t attrNames[16];
    uint32_t compCounts[16];
    uint32_t types[16];
    size_t offsets[16];
    uint32_t stride;
} VBLayout;
VBLayout *VBLayout_init(VBLayout *vbl);
VBLayout *VBLayout_addAttr(VBLayout *vbl, uint32_t attrName, uint32_t compCount, uint32_t type);
typedef struct VBO
{
    uint32_t id;
    VBLayout *layout;
    float *data;
} VBO;
VBO *VBO_init(VBO *vbo, VBLayout *layout);
VBO *VBO_uploadBuffer(VBO *vbo, size_t vCount);

typedef struct Mesh
{
    float *pointer;
    uint32_t vCount;
} Mesh;

typedef struct MeshArray
{
    VBO *vbo;
    size_t meshCount;
    size_t maxMeshes;
    Mesh **meshes;
} MeshArray;
MeshArray *MeshArray_initMeshArray(MeshArray *ma, VBO *vbo, size_t maxMeshes);
MeshArray *MeshArray_registerMesh(MeshArray *ma, Mesh *mesh);
MeshArray *MeshArray_packVBO(MeshArray *ma);

// temporary
MeshArray *makeBasicMeshArray(uint32_t pos_loc, uint32_t color_loc);