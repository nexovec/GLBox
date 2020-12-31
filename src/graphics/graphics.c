#include "graphics/graphics.h"
#include "glad/glad.h"

VBLayout *VBLayout_init(VBLayout *vbl){
    vbl->count = 0;
    vbl->stride = 0;
    return vbl;
}
// FIXME: only works for float because sizeof(float) is used in stride comp.
VBLayout *VBLayout_addAttr(VBLayout *vbl, uint32_t attrName, uint32_t compCount, uint32_t type, uint32_t offset){
    // TODO: guards for sizes in debug
    uint32_t i = vbl->count;
    vbl->compCounts[i] = compCount;
    vbl->types[i] = type;
    vbl->offsets[i] = offset;
    vbl->stride+=compCount*sizeof(float);
    vbl->count++;
    return vbl;
}
// FIXME: depends on VA state creep and pre-enabled attribute names
VBO *VBO_init(VBO *vbo,VBLayout *vbl, float *data, size_t count){
    vbo->layout = vbl;
    vbo->data = data;
    vbo->count = count;
    glad_glGenBuffers(1, &vbo->id);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
    // TODO: fix GL_STATIC_DRAW
    glad_glBufferData(GL_ARRAY_BUFFER, count*sizeof(float), vbo->data, GL_STATIC_DRAW);
    glad_glVertexAttribPointer(vbl->attrNames[0],vbl->compCounts[0],vbl->types[0],GL_FALSE,vbl->stride,(const void*)vbl->offsets[0]);
    // for(uint32_t i = 0;i<vbl->count;i++)
    // glad_glVertexAttribPointer(vbl->attrNames[i],vbl->compCounts[i],vbl->types[i],GL_FALSE,vbl->stride,(const void*)vbl->offsets[i]);
    return vbo;
}