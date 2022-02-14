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
MeshArray::MeshArray()
{
    // FIXME: Don't use C++
}
MeshArray::MeshArray(MeshArray *other)
{
    this->vbo = other->vbo;
    this->meshCount = other->meshCount;
    this->maxMeshes = other->maxMeshes;
    this->meshes = other->meshes;
}

MeshArray::MeshArray(VBO *vbo, size_t maxMeshes)
{
    this->vbo = vbo;
    this->meshCount = 0;
    this->maxMeshes = maxMeshes;
    // FIXME: leaks
    this->meshes = (Mesh **)calloc(sizeof(Mesh), this->maxMeshes);
}

MeshArray::~MeshArray()
{
    // TODO:
    // free(this->meshes);
}

void MeshArray::registerMesh(Mesh *mesh)
{
    if (this->maxMeshes == this->meshCount - 1)
    {
        printf("MeshArray is full");
        return;
    }
    this->meshes[this->meshCount++] = mesh;
    return;
}

void MeshArray::packVBO()
{
    int vCounter = 0;
    for (int i = 0; i < this->meshCount; i++)
    {
        int v1 = vCounter;
        int v2 = 6 * (this->meshes[i]->vCount);
        // FIXME: leaks BIG TIME
        this->vbo->data = concatFloatArrays(this->vbo->data, v1, this->meshes[i]->pointer, v2);
        vCounter += v2;
    }
    this->vbo->vCount = this->getVCount();
    VBO_uploadBuffer(this->vbo, this->vbo->vCount);
    return;
}

MeshArray MeshArray::makeBasicMeshArray(uint32_t pos_loc, uint32_t color_loc, BarChart *barchart)
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
    // MeshArray *ma = (MeshArray *)malloc(sizeof(MeshArray));
    MeshArray *ma = new MeshArray(vbo, 1000);
    // assert(ma != nullptr);
    // MeshArray_initMeshArray(ma, vbo, 1000);
    size_t meshCount = barchart->numOfEntries + 1;
    Mesh **meshes = barchart->meshifyChart();
    for (int i = 0; i < meshCount; i++)
        ma->registerMesh(meshes[i]);
    // MeshArray_registerMesh(&ma, meshes[i]);
    ma->packVBO();
    // MeshArray_packVBO(&ma);
    return MeshArray(ma);
}
// uint32_t getMeshArrayVCount(MeshArray *arr)
uint32_t MeshArray::getVCount()
{
    uint32_t res = 0;
    for (int i = 0; i < this->meshCount; i++)
    {
        if (this->meshes[i] == 0)
            break;
        res += this->meshes[i]->vCount;
    }
    return res;
}