


#ifndef PROJEKT_1_BENCHMARKSAVER_H
#define PROJEKT_1_BENCHMARKSAVER_H
// Writes aggregated benchmark results for AVL chaining,
// list chaining and open addressing hash tables to CSV files.
#include <string>
#include "DynamicArray.h"
class BenchmarkSaver {
public:
    static void saveOperationResults(
        const std::string& filename,
        int sizes[],
        const DynamicArray<long long>& avlAverages,
        const DynamicArray<long long>& listAverages,
        const DynamicArray<long long>& openAverages,
        int count
    );
};

#endif //PROJEKT_1_BENCHMARKSAVER_H
