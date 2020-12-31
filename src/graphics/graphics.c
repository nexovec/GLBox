#include "graphics/graphics.h"
#include "glad/glad.h"
#include "stdlib.h"

// TODO: other types than float
BufferAssembler *BufferAssembler_init(BufferAssembler *asm, VBLayout *vbl)
{
    asm->vbl = vbl;
    asm->index = 0;
    return asm;
}

BufferAssembler *BufferAssembler_addSegment(BufferAssembler *asm, float *segment)
{
    asm->segments[asm->index++] = segment;
    return asm;
}
float *BufferAssembler_getBufferData(BufferAssembler *asm, uint32_t vertexCount)
{
    // TODO: untested
    // TODO: remove malloc
    size_t finalSize = 0;
    for (uint32_t i = 0; i < asm->vbl->count; i++)
        finalSize += asm->vbl->compCounts[i];
    float *res = (float *)malloc(finalSize * sizeof(float));
    for (uint32_t a = 0; a < asm->vbl->count; a++)
    {
        for (uint32_t v = 0; v < vertexCount; v++)
        {
            for (uint32_t c = 0; c < asm->vbl->compCounts[a]; c++)
                res[asm->vbl->offsets[a] + v * asm->vbl->stride] = asm->segments[a][v * asm->vbl->compCounts[a] + c];
        }
    }
    return res;
}


VBLayout *VBLayout_init(VBLayout *vbl)
{
    vbl->count = 0;
    vbl->stride = 0;
    return vbl;
}
VBLayout *VBLayout_addAttr(VBLayout *vbl, uint32_t attrName, uint32_t compCount, uint32_t type, uint32_t offset)
{
    // TODO: guards for sizes in debug
    uint32_t i = vbl->count;
    vbl->attrNames[i] = attrName;
    vbl->compCounts[i] = compCount;
    vbl->types[i] = type;
    vbl->offsets[i] = offset;
    vbl->stride += compCount * sizeof(float);
    vbl->count++;
    return vbl;
}

// FIXME: depends on VA state creep and pre-enabled attribute names
VBO *VBO_init(VBO *vbo, VBLayout *vbl, float *data, size_t count)
{
    vbo->layout = vbl;
    vbo->data = data;
    vbo->count = count;
    glad_glGenBuffers(1, &vbo->id);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
    // TODO: fix GL_STATIC_DRAW
    glad_glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vbo->data, GL_STATIC_DRAW);
    // printf("%d %d %d %d %d %d\n", vbl->attrNames[0], vbl->compCounts[0], vbl->types[0], GL_FALSE, vbl->stride, (const void *)vbl->offsets[0]);
    // glad_glVertexAttribPointer(vbl->attrNames[0], vbl->compCounts[0], vbl->types[0], GL_FALSE, vbl->stride, (const void *)vbl->offsets[0]);
    for (uint32_t i = 0; i < vbl->count; i++)
    {
        // printf("%d %d\n", sizeof(&vbl->offsets[i]), sizeof(const void *));
        glad_glEnableVertexAttribArray(vbl->attrNames[i]);
        glad_glVertexAttribPointer(vbl->attrNames[i], vbl->compCounts[i], vbl->types[i], GL_FALSE, vbl->stride, (const void *)vbl->offsets[i]);
    }
    return vbo;
}