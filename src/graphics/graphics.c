#include "graphics/graphics.h"
#include "glad/glad.h"
#include "assert.h"
#include "stdlib.h"

VBLayout *VBLayout_init(VBLayout *vbl)
{
    vbl->attrCount = 0;
    vbl->stride = 0;
    vbl->offsets[0] = 0;
    return vbl;
}
// FIXME: only works for float because sizeof(float) is used in stride comp.
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

MeshArray *MeshArray_initMeshArray(VBO *vbo, size_t maxMeshes)
{
    //FIXME: leaks
    MeshArray *res = malloc(sizeof(MeshArray));
    return res;
}