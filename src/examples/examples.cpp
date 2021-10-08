#include "examples.hpp"
#include "algorithms/sequences.hpp"
#include "utils/utils.hpp"
#include "stdlib.h"
#define ENTRIES 10
BarChart makeSampleBarChart()
{
    BarChart res;
    res.numOfEntries = ENTRIES;
    res.colors = (int *)malloc((res.numOfEntries + 1) * sizeof(int));
    uint32_t entries[ENTRIES];
    // rangeIntSequence(entries,res.numOfEntries,1,1);
    randIntSequence((int32_t *)entries, res.numOfEntries, 1, 300);
    res.entries = (float *)malloc(res.numOfEntries * sizeof(float));
    for (uint32_t i = 0; i < res.numOfEntries; i++)
        res.entries[i] = (float)entries[i];
    printFloatArr(res.entries, ENTRIES);
    return res;
}