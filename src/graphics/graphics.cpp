#include "graphics/graphics.hpp"
#include "primitives.hpp"
#include "graphing/graphing.hpp"
#include "utils/utils.hpp"
#include "glad/glad.h"
#include "assert.h"
#include "stdlib.h"
#include "stdio.h"

VB_Layout::VB_Layout()
{
    this->attr_count = 0;
    this->stride = 0;
    this->offsets[0] = 0;
}
// FIXME: only works for float
VB_Layout *VB_Layout::add_attr(uint32_t attrName, uint32_t compCount, uint32_t type)
{
    // TODO: guards for sizes in debug
    uint32_t i = this->attr_count++;
    this->attr_names[i] = attrName;
    this->comp_counts[i] = compCount;
    this->types[i] = type;
    if (i)
        this->offsets[i] = this->offsets[i - 1] + this->comp_counts[i - 1] * sizeof(float);
    if (i == 1)
        assert(this->offsets[i] == 12);
    this->stride += compCount * sizeof(float);
    return this;
}
VBO::VBO(VB_Layout *layout) : layout(layout)
{
    // FIXME: Don't use C++
}
// FIXME: depends on VA state creep and pre-enabled attribute names
void VBO::upload_buffer(size_t v_count)
{
    glad_glGenBuffers(1, &this->id);
    glad_glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glad_glBufferData(GL_ARRAY_BUFFER, v_count * this->layout->stride, this->data, GL_DYNAMIC_DRAW);
    for (uint32_t i = 0; i < this->layout->attr_count; i++)
    {
        glad_glEnableVertexAttribArray(this->layout->attr_names[i]);
        glad_glVertexAttribPointer(this->layout->attr_names[i], this->layout->comp_counts[i], this->layout->types[i], GL_FALSE, this->layout->stride, (const void *)this->layout->offsets[i]);
    }
}
Mesh_Array::Mesh_Array()
{
    // FIXME: Don't use C++
}
Mesh_Array::Mesh_Array(Mesh_Array *other)
{
    this->vbo = other->vbo;
    this->mesh_count = other->mesh_count;
    this->max_meshes = other->max_meshes;
    this->meshes = other->meshes;
}

Mesh_Array::Mesh_Array(VBO *vbo, size_t max_meshes)
{
    this->vbo = vbo;
    this->mesh_count = 0;
    this->max_meshes = max_meshes;
    // FIXME: leaks
    this->meshes = (Mesh **)calloc(sizeof(Mesh), this->max_meshes);
}

Mesh_Array::~Mesh_Array()
{
    // TODO:
    // free(this->meshes);
}

void Mesh_Array::register_mesh(Mesh *mesh)
{
    if (this->max_meshes == this->mesh_count - 1)
    {
        printf("Mesh_Array is full");
        return;
    }
    this->meshes[this->mesh_count++] = mesh;
    return;
}

void Mesh_Array::pack_VBO()
{
    int vCounter = 0;
    for (int i = 0; i < this->mesh_count; i++)
    {
        int v1 = vCounter;
        int v2 = 6 * (this->meshes[i]->v_count);
        // FIXME: leaks BIG TIME
        this->vbo->data = concat_float_arrays(this->vbo->data, v1, this->meshes[i]->pointer, v2);
        vCounter += v2;
    }
    this->vbo->v_count = this->get_vertex_count();
    this->vbo->upload_buffer(this->vbo->v_count);
    return;
}

Mesh_Array Mesh_Array::make_basic_mesh_array(uint32_t pos_loc, uint32_t color_loc, Bar_Chart *barchart)
{
    uint32_t vao;
    glad_glGenVertexArrays(1, &vao);
    glad_glBindVertexArray(vao);
    // FIXME: leaks
    VB_Layout *vbl = new VB_Layout();
    // VB_Layout *vbl = (VB_Layout *)malloc(sizeof(VB_Layout));
    // vbl->init();
    vbl->add_attr(pos_loc, 3, GL_FLOAT);
    vbl->add_attr(color_loc, 3, GL_FLOAT);
    // FIXME: leaks
    VBO *vbo = new VBO(vbl);
    // vbo = (VBO *)malloc(sizeof(VBO));
    // VBO_init(vbo, vbl);
    // vbo->init(vbl);
    // Mesh_Array *ma = (Mesh_Array *)malloc(sizeof(Mesh_Array));
    Mesh_Array ma = Mesh_Array(vbo, 1000);
    // assert(ma != nullptr);
    // MeshArray_initMeshArray(ma, this, 1000);
    size_t mesh_count = barchart->num_of_entries + 1;
    Mesh **meshes = barchart->meshify_chart();
    for (int i = 0; i < mesh_count; i++)
        ma.register_mesh(meshes[i]);
    // MeshArray_registerMesh(&ma, meshes[i]);
    ma.pack_VBO();
    // MeshArray_packVBO(&ma);
    return ma;
}
// uint32_t getMeshArrayVCount(Mesh_Array *arr)
uint32_t Mesh_Array::get_vertex_count()
{
    uint32_t res = 0;
    for (int i = 0; i < this->mesh_count; i++)
    {
        if (this->meshes[i] == 0)
            break;
        res += this->meshes[i]->v_count;
    }
    return res;
}