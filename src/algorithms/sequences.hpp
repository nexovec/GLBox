#pragma once
#include <stdint.h>
#include <vector>
int *rangeIntSequence(int32_t *arr, int32_t n, int32_t lowerBound, int32_t jump);
int *randIntSequence(int32_t *arr, int32_t n, int32_t lowerbound, int32_t spread);


// NOTE: This is utterly ridiculous:
template <typename T>
concept can_make_sequence = requires(T v)
{
    v.operator+();
    v.operator*();
};
template <typename T>
requires can_make_sequence<T>
    std::vector<T> rangeSequence(std::vector<T> arr, T n, T lowerBound, T jump);