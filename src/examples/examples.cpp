#include "examples.h"
#include "algorithms/sequences.h"
#include "utils/utils.h"
#include "stdlib.h"
#define ENTRIES 10
BarChart makeSampleBarChart()
{
    BarChart res;
    res.numOfEntries = ENTRIES;
    res.colors = malloc((res.numOfEntries + 1) * sizeof(int));
    uint32_t entries[ENTRIES];
    // rangeIntSequence(entries,res.numOfEntries,1,1);
    randIntSequence(entries, res.numOfEntries, 1, 300);
    res.entries = malloc(res.numOfEntries * sizeof(float));
    for (uint32_t i = 0; i < res.numOfEntries; i++)
        res.entries[i] = (float)entries[i];
    printFloatArr(res.entries, ENTRIES);
    return res;
}