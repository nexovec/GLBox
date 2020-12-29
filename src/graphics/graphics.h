#include "mymath/mymath.h"
#include "stdint.h"
// FIXME: leaks
typedef struct VBO{
    uint32_t id;
    Vec3f *positions;
    Vec3f *colors;
}VBO;
