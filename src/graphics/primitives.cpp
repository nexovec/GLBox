#include "pch.hpp"
#include "graphics.hpp"
#include "mymath/mymath.hpp"
#include "utils/utils.hpp"
#include "stdlib.h"

// FIXME: assumes VB_Layout
float *make_triangle_arr(Vec3f *v1, Vec3f *v2, Vec3f *v3, Vec3f *color)
{
    float *p = (float *)malloc(3 * (3 * 2) * sizeof(float));
    p[0] = v1->x;
    p[1] = v1->y;
    p[2] = p[8] = p[14] = 0.f;
    p[6] = v2->x;
    p[7] = v2->y;
    p[12] = v3->x;
    p[13] = v3->y;
    for (int i = 0; i < 3; i++)
        for (int ii = 0; ii < 3; ii++)
            p[i * 6 + 3 + ii] = ((float *)color)[ii];
    return p;
}

Mesh *make_quad_mesh(Vec3f *pos, Vec3f *size, int col)
{
    // FIXME: leaks
    Mesh *res = (Mesh *)malloc(sizeof(Mesh));
    Vec3f color_vec;
    color_vec_from_enum(&color_vec, col);
    Vec3f first_triangle_v1 = {pos->x, pos->y, 0};
    Vec3f first_triangle_v2 = {pos->x + size->x, pos->y + size->y, 0};
    Vec3f first_triangle_v3 = {pos->x, pos->y + size->y, 0};
    Vec3f second_triangle_v1 = {pos->x, pos->y, 0};
    Vec3f second_triangle_v2 = {pos->x + size->x, pos->y, 0};
    Vec3f second_triangle_v3 = {pos->x + size->x, pos->y + size->y, 0};
    res->pointer = concat_float_arrays(
        make_triangle_arr(
            &first_triangle_v1,
            &first_triangle_v2,
            &first_triangle_v3,
            &color_vec),
        18,
        make_triangle_arr(
            &second_triangle_v1,
            &second_triangle_v2,
            &second_triangle_v3,
            &color_vec),
        18);
    res->v_count = 6;
    return res;
}

// temporary
Mesh *make_simple_triangle_mesh()
{
    // FIXME: leaks
    Mesh *res = (Mesh *)malloc(sizeof(Mesh));
    // FIXME: naming
    Vec3f first = {20, 20, 0};
    Vec3f second = {350, 350, 0};
    Vec3f third = {20, 350, 0};
    Vec3f fourth = {0.8f, 0.4f, 0.2f};
    res->pointer = make_triangle_arr(&first, &second, &third, &fourth);
    return res;
}
// temporary
Mesh *make_simple_quad_mesh()
{
    Mesh *m1;
    Mesh *m2;
    {
        Vec3f first = {20, 20, 0};
        Vec3f second = {350, 350, 0};
        m1 = make_quad_mesh(&first, &second, COLOR_BLUE);
    }
    {
        Vec3f first = {400, 400, 0};
        Vec3f second = {100, 100, 0};
        m2 = make_quad_mesh(&first, &second, COLOR_BLACK);
    }
    // FIXME: leaks
    Mesh *res = (Mesh *)malloc(sizeof(Mesh *));
    // FIXME: magic numbers
    res->pointer = concat_float_arrays(m1->pointer, 6 * m1->v_count, m2->pointer, 6 * m2->v_count);
    res->v_count = m1->v_count + m2->v_count;
    return res;
}