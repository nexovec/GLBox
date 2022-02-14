#include "pch.hpp"
#include "sequences.hpp"
#include <stdlib.h>
#include <stdint.h>

int *rangeIntSequence(int *arr, int n, int lowerBound, int jump)
{
    for(int i = 0;i<n;i++){
        arr[i] = lowerBound+jump*i;
    }
    return arr;
}
int *randIntSequence(int32_t *arr, int32_t n, int32_t lowerBound, int32_t spread){
    srand(25624);
    for(int32_t i = 0;i<n;i++){
        int32_t rd = (rand() % spread)+lowerBound;
        arr[i] = rd;
    }
    return arr;
}