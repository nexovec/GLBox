#include "pch.hpp"
// #include "common_defines.hpp"
// #include "platform_layer.hpp"
#include "super_math.hpp"
#include "stdint.h"
#include <string.h>
#include <cmath> // FIXME: reconsider
#include <limits>
#include <assert.h>

Vec2_f Vec2_f::operator+(const Vec2_f &other)
{
    return Vec2_f{x + other.x, y + other.y};
}

Vec2_f Vec2_f::operator-(const Vec2_f &other)
{
    return Vec2_f{x - other.x, y - other.y};
}

Vec2_f Vec2_f::operator*(float other) const
{
    return {this->x * other, this->y * other};
}

float Vec2_f::operator*(Vec2_f other) const
{
    // NOTE: computes dot product
    return other.x * (this->x) + other.y * (this->y);
}

constexpr Vec2_f Vec2_f::DOWN()
{
    // TODO: test this is 0 cost
    return {-1., 0.};
}

constexpr Vec2_f Vec2_f::UP()
{
    // TODO: test this is 0 cost
    return {1., 0.};
}

constexpr Vec2_f Vec2_f::LEFT()
{
    // TODO: test this is 0 cost
    return {0., -1.};
}

constexpr Vec2_f Vec2_f::RIGHT()
{
    // TODO: test this is 0 cost
    return {0., 1.};
}

// TODO: use templates and using for vectors?
Vec4_f Vec4_f::operator+(const Vec4_f &other)
{
    return {other.x + this->x, other.y + this->y, other.z + this->z, other.w + this->w};
}

Vec4_f Vec4_f::operator-(const Vec4_f &other)
{
    return {other.x - this->x, other.y - this->y, other.z - this->z, other.w - this->w};
}

Vec4_f Vec4_f::operator-() const
{
    return {-this->x, -this->y, -this->z, -this->w};
}

Vec4_f Vec4_f::operator*(float m) const
{
    return {m * this->x, m * this->y, m * this->z, m * this->w};
}

Vec4_f Vec4_f::operator/(float m) const
{
    return {this->x / m, this->y / m, this->z / m, this->w / m};
}

float Vec4_f::operator*(Vec4_f &m) const
{
    return m.x * this->x + m.y * this->y + m.z * this->z + m.w * this->w;
}

Vec4_ui Vec4_ui::operator+(const Vec4_ui &other)
{
    return {other.x + this->x, other.y * this->y, other.z * this->z, other.w * this->w};
}

Vec4_ui Vec4_ui::operator-(const Vec4_ui &other)
{
    return {other.x + this->x, other.y * this->y, other.z * this->z, other.w * this->w};
}

Vec4_ui Vec4_ui::operator*(int32_t m) const
{
    return {m * this->x, m * this->y, m * this->z, m * this->w};
}

float Vec4_ui::operator*(Vec4_ui &m) const
{
    return m.x * this->x + m.y * this->y + m.z * this->z + m.w * this->w;
}

Vec4_f Mat4_f::operator*(Vec4_f &other) const
{
    // PERFORMANCE: use SIMD
    Vec4_f result = {};
    float *res_unpacked = (float *)&result;
    for (int32_t y = 0; y < 4; y++)
    {
        for (int32_t x = 0; x < 4; x++)
        {
            res_unpacked[y] += this->row_aligned_elems[y * 4 + x] * ((float *)&other)[x];
        }
    }
    return result;
}

Mat4_f *Mat4_f::transposed()
{
    // TODO: test
    Mat4_f result;
    for (int32_t x = 0; x < 4; x++)
    {
        for (int32_t y = 0; y < 4; y++)
        {
            // PERFORMANCE: swap more intelligently?
            result.row_aligned_elems[y * 4 + x] = this->row_aligned_elems[x * 4 + y];
            result.row_aligned_elems[x * 4 + y] = this->row_aligned_elems[y * 4 + x];
        }
    }
    return (Mat4_f *)this;
}

Mat4_f *Mat4_f::in_place_transpose()
{
    // NOTE: transposes the matrix in-place and returns a pointer to it.
    // TODO: test
    // PERFORMANCE: in_place_transpose() vs transposed_matrix() perf test
    for (int32_t y = 0; y < 4; y++)
    {
        for (int32_t x = y; x < 4; x++)
        {
            // TODO: swap more intelligently?
            float holder = this->row_aligned_elems[y * 4 + x];
            this->row_aligned_elems[y * 4 + x] = this->row_aligned_elems[y * 4 + x];
            this->row_aligned_elems[x * 4 + y] = holder;
        }
    }
    return this;
}

Mat4_f Mat4_f::zero_matrix()
{
    // TODO: test
    return {};
}

Mat4_f Mat4_f::unit_matrix()
{
    return {
        1., 0., 0., 0.,
        0., 1., 0., 0.,
        0., 0., 1., 0.,
        0., 0., 0., 1.};
}

Mat4_f Mat4_f::ones()
{
    return {
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f};
}

static Mat4_f mat4f_rotation_x(float rot)
{
    Mat4_f s_e_mat = Mat4_f::unit_matrix();
    float c = (float)cos(rot);
    float s = (float)sin(rot);
    s_e_mat.row_aligned_elems[5] = c;
    s_e_mat.row_aligned_elems[6] = s;
    s_e_mat.row_aligned_elems[9] = -s;
    s_e_mat.row_aligned_elems[10] = c;
    return s_e_mat;
}

static Mat4_f mat4f_rotation_y(float rot)
{
    Mat4_f s_e_mat = Mat4_f::unit_matrix();
    float c = (float)cos(rot);
    float s = (float)sin(rot);
    s_e_mat.row_aligned_elems[0] = c;
    s_e_mat.row_aligned_elems[8] = s;
    s_e_mat.row_aligned_elems[2] = -s;
    s_e_mat.row_aligned_elems[10] = c;
    return s_e_mat;
}

static Mat4_f mat4f_rotation_z(float rot)
{
    Mat4_f s_e_mat = Mat4_f::unit_matrix();
    float c = (float)cos(rot);
    float s = (float)sin(rot);
    s_e_mat.row_aligned_elems[0] = c;
    s_e_mat.row_aligned_elems[1] = s;
    s_e_mat.row_aligned_elems[4] = -s;
    s_e_mat.row_aligned_elems[5] = c;
    return s_e_mat;
}

Mat4_f Mat4_f::rotation_matrix(Vec4_f &rot)
{
    return Mat4_f::rotation_matrix(rot.x, rot.y, rot.z);
}

Mat4_f Mat4_f::rotation_matrix(float x_rot, float y_rot, float z_rot)
{
    // TODO: test
    // PERFORMANCE: you can just use general prescription for a rotation matrix instead of doing two multiplications
    Mat4_f x = mat4f_rotation_x(x_rot);
    Mat4_f y = mat4f_rotation_y(y_rot);
    Mat4_f z = mat4f_rotation_z(z_rot);
    return x * y * z;
}

Mat4_f Mat4_f::translation_matrix(Vec4_f translation)
{
    Mat4_f result = Mat4_f::unit_matrix();
    result.row_aligned_elems[0 * 4 + 3] = translation.x;
    result.row_aligned_elems[1 * 4 + 3] = translation.y;
    result.row_aligned_elems[2 * 4 + 3] = translation.z;
    return result;
}

Mat4_f Mat4_f::ortho_projection_matrix(float left, float right, float top, float bottom, float near, float far)
{
    // TODO: test
    // return {
    //     2 / (r - l), 0,           0,           -(r + l) / (r - l),
    //     0,           2 / (t - b), 0,           -(t + b) / (t - b),
    //     0,           0,          -2 * (n - f), -(f + n) / (f - n),
    //     0,           0,           0,            1
    //     };
    Mat4_f mat = Mat4_f::unit_matrix();
    mat.row_aligned_elems[0] = 2.f / (right - left);
    mat.row_aligned_elems[5] = 2.f / (top - bottom);
    mat.row_aligned_elems[10] = 2.f / (near - far);
    mat.row_aligned_elems[14] = -(far + near) / (far - near);
    mat.row_aligned_elems[13] = -(top + bottom) / (top - bottom);
    mat.row_aligned_elems[12] = -(right + left) / (right - left);
    return mat;
}

/**
 * Same as ortho projection, but it converts to screen coordinates with 0 in lower left corner.
 **/
Mat4_f Mat4_f::screen_ortho_projection_matrix(float left, float right, float top, float bottom, float near, float far)
{
    // PERFORMANCE: slow, make mat4_f::ortho_projection_scaled() that projects into screen space directly
    return (Mat4_f::ortho_projection_matrix(left, right, top, bottom, near, far) * 0.5f) + Mat4_f::translation_matrix({0.5f, 0.5f, 0.5f});
}

Mat4_f Mat4_f::operator*(float scale) const
{
    Vec4_f *elems = (Vec4_f *)this->row_aligned_elems;
    Vec4_f back[4] = {elems[0] * scale, elems[1] * scale, elems[2] * scale, elems[3] * scale};
    return *((Mat4_f *)&back);
}

Mat4_f Mat4_f::operator-(Mat4_f other) const
{
    Mat4_f mat;
    for (int i = 0; i < 16; i++)
    {
        mat.row_aligned_elems[i] = this->row_aligned_elems[i] - other.row_aligned_elems[i];
    }
    return mat;
}

Mat4_f Mat4_f::operator-() const
{
    Mat4_f mat;
    for (int i = 0; i < 16; i++)
    {
        mat.row_aligned_elems[i] = -this->row_aligned_elems[i];
    }
    return mat;
}

Mat4_f Mat4_f::operator+(Mat4_f other) const
{
    Mat4_f mat;
    for (int i = 0; i < 16; i++)
    {
        mat.row_aligned_elems[i] = this->row_aligned_elems[i] + other.row_aligned_elems[i];
    }
    return mat;
}

Mat4_f Mat4_f::operator*(Mat4_f other) const
{
    // TODO: test
    Mat4_f mat = Mat4_f::zero_matrix();
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            for (int i = 0; i < 4; i++)
            {
                mat.row_aligned_elems[x + 4 * y] += this->row_aligned_elems[y * 4 + i] * other.row_aligned_elems[x + i * 4];
            }
        }
    }
    return mat;
}

Mat4_f Mat4_f::perspective_projection_matrix(float fov, float aspect, float near, float far)
{
    // fov = math.PI / 180.0;
    assert(abs(aspect - std::numeric_limits<float>::epsilon()) > static_cast<float>(0));
    float yScale = 1.0 / tan(fov * fov / 2);
    float xScale = yScale / aspect;
    // float nearmfar = near - far;
    float const tanHalfFovy = tan(fov / static_cast<float>(2));
    Mat4_f mat = Mat4_f::unit_matrix();
    mat.row_aligned_elems[0 * 4 + 0] = static_cast<float>(1) / (aspect * tanHalfFovy);
    mat.row_aligned_elems[1 * 4 + 1] = static_cast<float>(1) / (tanHalfFovy);
    mat.row_aligned_elems[2 * 4 + 2] = far / (far - near);
    mat.row_aligned_elems[2 * 4 + 3] = static_cast<float>(1);
    mat.row_aligned_elems[3 * 4 + 2] = -(far * near) / (far - near);
    // memcpy(&mat.row_aligned_elems, members, 16 * sizeof(float));
    return mat;
}

Vec2_f Mat2_f::operator*(const Vec2_f vec)
{
    Vec2_f back;
    // TODO: investigate SIMD
    back.x = row_aligned_elems[0] * vec.x + row_aligned_elems[1] * vec.y;
    back.y = row_aligned_elems[2] * vec.x + row_aligned_elems[3] * vec.y;
    return back;
}

Mat2_f Mat2_f::zero_matrix()
{
    return {};
}

Mat2_f Mat2_f::unit_matrix()
{
    return {1.0f, 0.0f, 0.0f, 1.0f};
}

Mat2_f Mat2_f::rotation_matrix(float angle)
{
    Mat2_f matrix = {cos(angle), -sin(angle), sin(angle), cos(angle)};
    return matrix;
}

uint32_t interpolatedColor(float lam_1, float lam_2, float lam_3, uint32_t color1, uint32_t color2, uint32_t color3)
{
    // use solid color
    // return 0xff00ff00;

    //  ? TODO: for performance reasons, you should decompose colors per-triangle, not per-pixel, but bitwise is fast and this won't be used anywway
    const uint8_t a1 = (uint8_t)(color1 >> 24);
    const uint8_t r1 = (uint8_t)(color1 >> 16);
    const uint8_t g1 = (uint8_t)(color1 >> 8);
    const uint8_t b1 = (uint8_t)(color1 >> 0);
    const uint8_t a2 = (uint8_t)(color2 >> 24);
    const uint8_t r2 = (uint8_t)(color2 >> 16);
    const uint8_t g2 = (uint8_t)(color2 >> 8);
    const uint8_t b2 = (uint8_t)(color2 >> 0);
    const uint8_t a3 = (uint8_t)(color3 >> 24);
    const uint8_t r3 = (uint8_t)(color3 >> 16);
    const uint8_t g3 = (uint8_t)(color3 >> 8);
    const uint8_t b3 = (uint8_t)(color3 >> 0);
    const uint8_t final_a = (uint8_t)(a1 * lam_1 + a2 * lam_2 + a3 * lam_3);
    const uint8_t final_r = (uint8_t)(r1 * lam_1 + r2 * lam_2 + r3 * lam_3);
    const uint8_t final_g = (uint8_t)(g1 * lam_1 + g2 * lam_2 + g3 * lam_3);
    const uint8_t final_b = (uint8_t)(b1 * lam_1 + b2 * lam_2 + b3 * lam_3);

    // return ((final_a&0xff) << 24) + ((final_r&0xff) << 16) + ((final_g&0xff) << 8) + final_b&0xff; // <- DEBUG
    return (final_a << 24) + (final_r << 16) + (final_g << 8) + final_b;
}