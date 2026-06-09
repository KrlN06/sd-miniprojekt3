
#ifndef PROJEKT_1_BENCHMARK_H
#define PROJEKT_1_BENCHMARK_H
#include "DynamicArray.h"
#include "HashTableChainingAVL.h"
#include "HashTableChainingList.h"
#include "HashTableOpenAddressing.h"


// Stores raw timings and per-size averages for the full benchmark suite.
class Benchmark {
public:
    // Runs all benchmarks for all structures
    void run();
    const static int SIZE = 50;

private:
    // The same size schedule is reused for every measured operation.
    int sizes[SIZE] = {
        5000, 8000, 10000, 12000, 14000,
        16000, 18000, 20000, 24000, 28000,
        32000, 36000, 40000, 44000, 48000,
        52000, 56000, 60000, 64000, 68000,
        72000, 76000, 80000, 84000, 88000,
        92000, 96000, 100000, 104000, 108000,
        112000, 116000, 120000, 124000, 128000,
        132000, 136000, 140000, 144000, 148000,
        152000, 156000, 160000, 165000, 170000,
        175000, 180000, 185000, 190000, 200000
    };

    // Current size results - AVL
    DynamicArray<long long> avlInsertResults;
    DynamicArray<long long> avlRemoveResults;;
    
    // Current size results - List
    DynamicArray<long long> listInsertResults;
    DynamicArray<long long> listRemoveResults;

    // Current size results - Open Addressing
    DynamicArray<long long> openInsertResults;
    DynamicArray<long long> openRemoveResults;

    // Tablice docelowe ze średnimi (zapisywane do plików CSV na samym końcu)
    DynamicArray<long long> avlInsertAverages;
    DynamicArray<long long> avlRemoveAverages;

    DynamicArray<long long> openInsertAverages;
    DynamicArray<long long> openRemoveAverages;

    DynamicArray<long long> listInsertAverages;
    DynamicArray<long long> listRemoveAverages;



    // Runs benchmark for dynamic array
    

    // Runs benchmark for AVL
    void benchmarkAvl(const HashTableChainingAVL& originalDictionary,
                               const DynamicArray<int>& data);

    // Runs benchmark list
    void benchmarkList(const HashTableChainingList& originalDictionary,
                              const DynamicArray<int>& data);

    // Runs benchmark for open addresing
    void benchmarkOpen(const HashTableOpenAddressing& originalDictionary,
                               const DynamicArray<int>& data);



    // Generates random data of given size
    DynamicArray<int> generateRandomData(int size);

    // Calculates average from collected results
    long long calculateAverage(const DynamicArray<long long>& results);

    // Displays results on screen
    void displayResults(int size);
};
#endif //PROJEKT_1_BENCHMARK_H
