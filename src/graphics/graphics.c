#include "graphics/graphics.h"
#include "graphics/primitives.h"
#include "glad/glad.h"
#include "assert.h"
#include "stdlib.h"
#include "stdio.h"

VBLayout *VBLayout_init(VBLayout *vbl)
{
    vbl->attrCount = 0;
    vbl->stride = 0;
    vbl->offsets[0] = 0;
    return vbl;
}
// FIXME: only works for float
VBLayout *VBLayout_addAttr(VBLayout *vbl, uint32_t attrName, uint32_t compCount, uint32_t type)
{
    // TODO: guards for sizes in debug
    uint32_t i = vbl->attrCount++;
    vbl->attrNames[i] = attrName;
    vbl->compCounts[i] = compCount;
    vbl->types[i] = type;
    if (i)
        vbl->offsets[i] = vbl->offsets[i - 1] + vbl->compCounts[i - 1] * sizeof(float);
    if (i == 1)
        assert(vbl->offsets[i] == 12);
    vbl->stride += compCount * sizeof(float);
    return vbl;
}
// FIXME: depends on VA state creep and pre-enabled attribute names
VBO *VBO_init(VBO *vbo, VBLayout *vbl, size_t vCount)
{
    glad_glGenBuffers(1, &vbo->id);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
    // TODO: fix GL_STATIC_DRAW
    glad_glBufferData(GL_ARRAY_BUFFER, vCount * vbl->stride * sizeof(float), vbo->data, GL_STATIC_DRAW);
    vbo->layout = vbl;
    for (uint32_t i = 0; i < vbl->attrCount; i++)
    {
        glad_glEnableVertexAttribArray(vbl->attrNames[i]);
        glad_glVertexAttribPointer(vbl->attrNames[i], vbl->compCounts[i], vbl->types[i], GL_FALSE, vbl->stride, (const void *)vbl->offsets[i]);
    }
    return vbo;
}

MeshArray *MeshArray_initMeshArray(MeshArray *ma, VBO *vbo, size_t maxMeshes)
{
    ma->vbo = vbo;
    ma->meshCount = 0;
    ma->maxMeshes = maxMeshes;
    //FIXME: leaks
    ma->meshes = calloc(sizeof(Mesh), ma->maxMeshes);
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
MeshArray *MeshArray_packVBO(MeshArray *ma, Mesh *mesh)
{
    // TODO: !!
    ma->meshes[0] = mesh;
    // temporary
    size_t s = mesh->vCount * (3 * 2) * sizeof(float);
    // FIXME: lol, not like this
    ma->meshCount = 1;
    ma->vbo->data = mesh->pointer;
    printf("\n%d", mesh->vCount);
    return ma;
}

//temporary
MeshArray *makeBasicMeshArray(uint32_t pos_loc, uint32_t color_loc)
{
    uint32_t vao;
    glad_glGenVertexArrays(1, &vao);
    glad_glBindVertexArray(vao);
    // FIXME: leaks
    VBLayout *vbl = malloc(sizeof(VBLayout));
    VBLayout_init(vbl);
    VBLayout_addAttr(vbl, pos_loc, 3, GL_FLOAT);
    VBLayout_addAttr(vbl, color_loc, 3, GL_FLOAT);
    VBO *vbo;
    // FIXME: leaks
    vbo = malloc(sizeof(VBO));
    MeshArray *ma = malloc(sizeof(MeshArray));
    MeshArray_initMeshArray(ma, vbo, 1000);

    MeshArray_packVBO(ma, makeSimpleQuadMesh());
    VBO_init(vbo, vbl, 12);
    return ma;
}
uint32_t getMeshArrayVCount(MeshArray *arr)
{
    uint32_t res = 0;
    for (int i = 0; i < arr->meshCount; i++)
    {
        if(arr->meshes[i] == 0) break;
        res += arr->meshes[i]->vCount;
    }
    return res;
}