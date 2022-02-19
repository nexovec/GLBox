#pragma once
#include "stdint.h"

struct Vec2_f
{
    float x;
    float y;
    Vec2_f operator+(const Vec2_f &other);
    Vec2_f operator-(const Vec2_f &other);
    Vec2_f operator*(float other) const;
    float operator*(Vec2_f other) const;
    constexpr static Vec2_f DOWN();
    constexpr static Vec2_f UP();
    constexpr static Vec2_f LEFT();
    constexpr static Vec2_f RIGHT();
};

struct Vec4_ui
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t w;
    Vec4_ui operator+(const Vec4_ui &other);
    Vec4_ui operator-(const Vec4_ui &other);
    Vec4_ui operator*(int32_t other) const;
    float operator*(Vec4_ui &other) const;
};

struct Vec4_f
{
    float x;
    float y;
    float z;
    float w;
    Vec4_f operator+(const Vec4_f &other);
    Vec4_f operator-(const Vec4_f &other);
    Vec4_f operator-() const;
    Vec4_f operator*(float other) const;
    Vec4_f operator/(float other) const;
    float operator*(Vec4_f &other) const;
};
struct Mat4_f
{
    float row_aligned_elems[16];
    Vec4_f operator*(Vec4_f &other) const;
    Mat4_f operator*(float scale) const;
    Mat4_f operator*(Mat4_f other) const;
    Mat4_f operator-(Mat4_f other) const;
    Mat4_f operator-() const;
    Mat4_f operator+(Mat4_f other) const;
    Mat4_f *transposed();
    Mat4_f *in_place_transpose();
    static Mat4_f zero_matrix();
    static Mat4_f unit_matrix();
    static Mat4_f ones();
    static Mat4_f rotation_matrix(Vec4_f &rot);
    static Mat4_f rotation_matrix(float x_rot, float y_rot, float z_rot);
    static Mat4_f translation_matrix(Vec4_f);
    static Mat4_f ortho_projection_matrix(float l, float r, float t, float b, float n, float f);
    static Mat4_f screen_ortho_projection_matrix(float l, float r, float t, float b, float n, float f);
    static Mat4_f perspective_projection_matrix(float fov, float aspect, float near, float far);
};

uint32_t interpolatedColor(float lam_1, float lam_2, float lam_3, uint32_t color1, uint32_t color2, uint32_t color3);

struct Mat2_f
{
    float row_aligned_elems[4]; // FIXME: There was a fixme here but I don't know why
    Vec2_f operator*(const Vec2_f vec);
    static Mat2_f unit_matrix();
    static Mat2_f zero_matrix();
    static Mat2_f rotation_matrix(float angle);
};

// TODO: have all of the following in one compilation unit
template <typename T>
inline T math_sgn(T n, T zero)
{
    return (n > 0) - (n < 0);
}

template <typename T>
inline T math_lerp(T a, T b, float ratio)
{
    return a + ratio * (b - a);
}

template <typename T>
inline float math_invLerp(T a, T b, float val)
{
    return (val - a) / (b - a);
}

template <typename T>
T clamp(T in, T min, T max)
{
    // PERFORMANCE: bruh. use MMX.
    if (in < min)
        return min;
    else if (in > max)
        return max;
    else
        return in;
}

template <typename T>
T max(T a, T b)
{
    // PERFORMANCE: bruh. use MMX.
    if (a > b)
        return a;
    else
        return b;
    // return ((a > b) * a) & ((a <= b) * b);
}

template <typename T>
T min(T a, T b)
{
    // PERFORMANCE: bruh. use MMX.
    if (a <= b)
        return a;
    else
        return b;
    // return (((a <= b) * a) & ((a > b) * b));
}