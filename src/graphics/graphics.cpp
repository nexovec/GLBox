#include "graphics/graphics.hpp"
#include "primitives.hpp"
#include "graphing/graphing.hpp"
#include "utils/utils.hpp"
#include "glad/glad.h"
#include "assert.h"
#include "stdlib.h"
#include "stdio.h"

VBLayout *VBLayout::init()
{
    this->attrCount = 0;
    this->stride = 0;
    this->offsets[0] = 0;
    return this;
}
// FIXME: only works for float
VBLayout *VBLayout::addAttr(uint32_t attrName, uint32_t compCount, uint32_t type)
{
    // TODO: guards for sizes in debug
    uint32_t i = this->attrCount++;
    this->attrNames[i] = attrName;
    this->compCounts[i] = compCount;
    this->types[i] = type;
    if (i)
        this->offsets[i] = this->offsets[i - 1] + this->compCounts[i - 1] * sizeof(float);
    if (i == 1)
        assert(this->offsets[i] == 12);
    this->stride += compCount * sizeof(float);
    return this;
}
VBO *VBO_init(VBO *vbo, VBLayout *layout)
{
    vbo->layout = layout;
    return vbo;
}
// FIXME: depends on VA state creep and pre-enabled attribute names
VBO *VBO_uploadBuffer(VBO *vbo, size_t vCount)
{
    glad_glGenBuffers(1, &vbo->id);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
    glad_glBufferData(GL_ARRAY_BUFFER, vCount * vbo->layout->stride, vbo->data, GL_DYNAMIC_DRAW);
    for (uint32_t i = 0; i < vbo->layout->attrCount; i++)
    {
        glad_glEnableVertexAttribArray(vbo->layout->attrNames[i]);
        glad_glVertexAttribPointer(vbo->layout->attrNames[i], vbo->layout->compCounts[i], vbo->layout->types[i], GL_FALSE, vbo->layout->stride, (const void *)vbo->layout->offsets[i]);
    }
    return vbo;
}

MeshArray *MeshArray_initMeshArray(MeshArray *ma, VBO *vbo, size_t maxMeshes)
{
    ma->vbo = vbo;
    ma->meshCount = 0;
    ma->maxMeshes = maxMeshes;
    //FIXME: leaks
    ma->meshes = (Mesh **)calloc(sizeof(Mesh), ma->maxMeshes);
    return ma;
}

MeshArray *MeshArray_registerMesh(MeshArray *ma, Mesh *mesh)
{
    if (ma->maxMeshes == ma->meshCount - 1)
    {
        printf("MeshArray is full");
        return ma;
    }
    ma->meshes[ma->meshCount++] = mesh;
    return ma;
}
MeshArray *MeshArray_packVBO(MeshArray *ma)
{
    int vCounter = 0;
    for (int i = 0; i < ma->meshCount; i++)
    {
        int v1 = vCounter;
        int v2 = 6 * (ma->meshes[i]->vCount);
        // FIXME: leaks BIG TIME
        ma->vbo->data = concatFloatArrays(ma->vbo->data, v1, ma->meshes[i]->pointer, v2);
        vCounter += v2;
    }
    ma->vbo->vCount = getMeshArrayVCount(ma);
    VBO_uploadBuffer(ma->vbo, ma->vbo->vCount);
    return ma;
}
MeshArray *makeBasicMeshArray(uint32_t pos_loc, uint32_t color_loc, BarChart *barchart)
{
    uint32_t vao;
    glad_glGenVertexArrays(1, &vao);
    glad_glBindVertexArray(vao);
    // FIXME: leaks
    VBLayout *vbl = (VBLayout *)malloc(sizeof(VBLayout));
    vbl->init();
    vbl->addAttr(pos_loc, 3, GL_FLOAT);
    vbl->addAttr(color_loc, 3, GL_FLOAT);
    VBO *vbo;
    // FIXME: leaks
    vbo = (VBO *)malloc(sizeof(VBO));
    VBO_init(vbo, vbl);
    MeshArray *ma = (MeshArray *)malloc(sizeof(MeshArray));
    assert(ma != nullptr);
    MeshArray_initMeshArray(ma, vbo, 1000);
    size_t meshCount = barchart->numOfEntries + 1;
    Mesh **meshes = meshifyChart(barchart);
    for (int i = 0; i < meshCount; i++)
        MeshArray_registerMesh(ma, meshes[i]);
    MeshArray_packVBO(ma);
    return ma;
}
uint32_t getMeshArrayVCount(MeshArray *arr)
{
    uint32_t res = 0;
    for (int i = 0; i < arr->meshCount; i++)
    {
        if (arr->meshes[i] == 0)
            break;
        res += arr->meshes[i]->vCount;
    }
    return res;
}