#include "Benchmark.h"
#include <cstdlib>
#include <iostream>

#include "Timer.h"
#include "Random.h"
#include "BenchmarkSaver.h"
#include "HashTableChainingAVL.h"
#include "HashTableChainingList.h"
#include "HashTableOpenAddressing.h"

void Benchmark::run() {

    // Test all configured structure sizes
    for (int size : sizes) {

        // Repeat benchmark multiple times for stable average results
        for (int i = 0; i < 100; i++) {

            // Generate common random dataset
            DynamicArray<int> data = generateRandomData(size);

            // Create fresh empty structures----------------------------------
            HashTableChainingAVL avl;
            HashTableChainingList list;
            HashTableOpenAddressing open;

            //------------------------------------------------------------------

            // Fill all structures with identical data------------------------
            for (int j = 0; j < data.getSize(); j++) {
                avl.insert(data[j], data[j]);
                list.insert(data[j], data[j]);
                open.insert(data[j], data[j]);
            }
            //------------------------------------------------------------------

            // Run benchmark operations--------------------------------------

            benchmarkAvl(avl, data);
            benchmarkList(list, data);
            benchmarkOpen(open, data);
        }
        // Display average results for current structure size
        displayResults(size);

        // Store averages for CSV saving for AVL chaining
        avlInsertAverages.push_back(calculateAverage(avlInsertResults));
        avlRemoveAverages.push_back(calculateAverage(avlRemoveResults));

        // Store averages for CSV saving for list chaining
        listInsertAverages.push_back(calculateAverage(listInsertResults));
        listRemoveAverages.push_back(calculateAverage(listRemoveResults));

        // Store averages for CSV saving for open addressing
        openInsertAverages.push_back(calculateAverage(openInsertResults));
        openRemoveAverages.push_back(calculateAverage(openRemoveResults));

        // Clear collected results before testing next size
        avlInsertResults.clear();
        avlRemoveResults.clear();

        listInsertResults.clear();
        listRemoveResults.clear();

        openInsertResults.clear();
        openRemoveResults.clear();

    }

    // Export CSV files for insert and remove operations only
    BenchmarkSaver::saveOperationResults(
        "insert_avl.csv",
        sizes,
        avlInsertAverages,
        listInsertAverages,
        openInsertAverages,
        SIZE
    );

    BenchmarkSaver::saveOperationResults(
        "remove_avl.csv",
        sizes,
        avlRemoveAverages,
        listRemoveAverages,
        openRemoveAverages,
        SIZE
    );
}


//========================================================================
// AVL CHAINING BENCHMARKS
//========================================================================

void Benchmark::benchmarkAvl(const HashTableChainingAVL& originalTable, const DynamicArray<int>& data) {
    Timer timer;
    const int repetitions = 100;
    // Each operation is performed on a copy of the original structure
    // to ensure identical starting conditions for every measurement

    {
        // Insert benchmark-----------------------------------------------
        long long totalTime = 0;
        for (int i = 0; i < repetitions; i++) {
            HashTableChainingAVL table = originalTable;
            int key = 1000000 + i;
            int value = key;
            timer.start();
            table.insert(key, value);
            timer.stop();
            totalTime += timer.getElapsedTime();
        }
        avlInsertResults.push_back(totalTime / repetitions);
    }
    //------------------------------------------------------------------
    // Remove benchmark--------------------------------------------------
    {
        long long totalTime = 0;
        for (int i = 0; i < repetitions; i++) {
            HashTableChainingAVL table = originalTable;
            int randomIndex = Random::generateRandomInt(0, data.getSize() - 1);
            int key = data[randomIndex];
            timer.start();
            table.remove(key);
            timer.stop();
            totalTime += timer.getElapsedTime();
        }
        avlRemoveResults.push_back(totalTime / repetitions);
    }
}


//========================================================================
// LIST CHAINING BENCHMARKS
//========================================================================

void Benchmark::benchmarkList(const HashTableChainingList& originalTable, const DynamicArray<int>& data) {
    Timer timer;
    const int repetitions = 100;
    // Each operation is performed on a copy of the original structure
    // to ensure identical starting conditions for every measurement

    {
        // Insert benchmark-----------------------------------------------
        long long totalTime = 0;
        for (int i = 0; i < repetitions; i++) {
            HashTableChainingList table = originalTable;
            int key = 1000000 + i;
            int value = key;
            timer.start();
            table.insert(key, value);
            timer.stop();
            totalTime += timer.getElapsedTime();
        }
        listInsertResults.push_back(totalTime / repetitions);
    }
    //------------------------------------------------------------------
    // Remove benchmark--------------------------------------------------
    {
        long long totalTime = 0;
        for (int i = 0; i < repetitions; i++) {
            HashTableChainingList table = originalTable;
            int randomIndex = Random::generateRandomInt(0, data.getSize() - 1);
            int key = data[randomIndex];
            timer.start();
            table.remove(key);
            timer.stop();
            totalTime += timer.getElapsedTime();
        }
        listRemoveResults.push_back(totalTime / repetitions);
    }
}


//========================================================================
// OPEN ADDRESSING BENCHMARKS
//========================================================================

void Benchmark::benchmarkOpen(const HashTableOpenAddressing& originalTable, const DynamicArray<int>& data) {
    Timer timer;
    const int repetitions = 100;
    // Each operation is performed on a copy of the original structure
    // to ensure identical starting conditions for every measurement

    {
        // Insert benchmark-----------------------------------------------
        long long totalTime = 0;
        for (int i = 0; i < repetitions; i++) {
            HashTableOpenAddressing table = originalTable;
            int key = 1000000 + i;
            int value = key;
            timer.start();
            table.insert(key, value);
            timer.stop();
            totalTime += timer.getElapsedTime();
        }
        openInsertResults.push_back(totalTime / repetitions);
    }
    //------------------------------------------------------------------
    // Remove benchmark--------------------------------------------------
    {
        long long totalTime = 0;
        for (int i = 0; i < repetitions; i++) {
            HashTableOpenAddressing table = originalTable;
            int randomIndex = Random::generateRandomInt(0, data.getSize() - 1);
            int key = data[randomIndex];
            timer.start();
            table.remove(key);
            timer.stop();
            totalTime += timer.getElapsedTime();
        }
        openRemoveResults.push_back(totalTime / repetitions);
    }
}




DynamicArray<int> Benchmark::generateRandomData(int size) {
    DynamicArray<int> data;

    // Fill the structure with random integer values
    for (int i = 0; i < size; i++) {
        data.push_back(Random::generateRandomInt(0, 99999));
    }

    return data;
}


long long Benchmark::calculateAverage(const DynamicArray<long long>& results) {
    // Sum all measured execution times stored in the results structure.
    // Then divide the total time by the number of measurements to get the average.

    if (results.isEmpty()) {
        return 0;
    }

    // Sum all measured times
    long long sum = 0;

    for (int i = 0; i < results.getSize(); i++) {
        sum += results[i];
    }

    // Return average execution time
    return sum / results.getSize();
}


void Benchmark::displayResults(int size) {
    // Display average benchmark results for current size
    std::cout << "Size: " << size << std::endl;

    // AVL Chaining results----------------------------------------
    std::cout << "\nAVL Chaining" << std::endl;
    std::cout << "Insert: " << calculateAverage(avlInsertResults) << " ns" << std::endl;
    std::cout << "Remove: " << calculateAverage(avlRemoveResults) << " ns" << std::endl;

    // List Chaining results----------------------------------------
    std::cout << "\nList Chaining" << std::endl;
    std::cout << "Insert: " << calculateAverage(listInsertResults) << " ns" << std::endl;
    std::cout << "Remove: " << calculateAverage(listRemoveResults) << " ns" << std::endl;

    // Open Addressing results----------------------------------------
    std::cout << "\nOpen Addressing" << std::endl;
    std::cout << "Insert: " << calculateAverage(openInsertResults) << " ns" << std::endl;
    std::cout << "Remove: " << calculateAverage(openRemoveResults) << " ns" << std::endl;
    
}
