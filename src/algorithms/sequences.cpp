#include "pch.hpp"
#include "sequences.hpp"
#include <stdlib.h>
#include <vector>
#include <stdint.h>

template <typename T>
T *rangeSequence(T *arr, T n, T lowerBound, T jump)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = lowerBound + jump * i;
    }
    return arr;
}
template <typename T>
requires can_make_sequence<T>
void rangeSequence(std::vector<T> arr, T n, T lowerBound, T jump)
{
    // TODO: test
    for (T i = (T)0; i < n; i++)
    {
        arr.push_back(lowerBound + i * jump);
    }
}
int *randIntSequence(int32_t *arr, int32_t n, int32_t lowerBound, int32_t spread)
{
    srand(25624);
    for (int32_t i = 0; i < n; i++)
    {
        int32_t rd = (rand() % spread) + lowerBound;
        arr[i] = rd;
    }
    return arr;
}