#include "sequences.h"
#include "stdlib.h"

int *rangeIntSequence(int *arr, int n, int lowerBound, int jump)
{
    for(int i = 0;i<n;i++){
        arr[i] = lowerBound+jump*i;
    }
    return arr;
}
int *randIntSequence(int *arr, int n, int lowerBound, int spread){
    srand(25624);
    for(int i = 0;i<n;i++){
        int rd = (rand() % spread)+lowerBound;
        arr[i] = rd;
    }
    return arr;
}