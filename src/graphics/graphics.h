#include "mymath/mymath.h"
#include "stdint.h"
// FIXME: leaks
typedef struct VBLayout{
    uint32_t count;
    uint32_t attrNames[16];
    uint32_t compCounts[16];
    uint32_t types[16];
    uint32_t offsets[16];
    uint32_t stride;
}VBLayout;
VBLayout *VBLayout_init(VBLayout *vbl);
VBLayout *VBLayout_addAttr(VBLayout *vbl, uint32_t attrName, uint32_t compCount, uint32_t type, uint32_t offset);
typedef struct VBO{
    uint32_t id;
    VBLayout *layout;
    float *data;
    size_t count;
}VBO;
VBO *VBO_init(VBO *vbo, VBLayout *vbl, float *data, size_t count);
