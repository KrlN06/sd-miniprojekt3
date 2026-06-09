
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "BenchmarkSaver.h"

void BenchmarkSaver::saveOperationResults(
    const std::string& filename,
    int sizes[],
    const DynamicArray<long long>& avlAverages,
    const DynamicArray<long long>& listAverages,
    const DynamicArray<long long>& openAverages,
    int count
) {
    // Keep benchmark exports in a dedicated folder.
    std::filesystem::create_directory("results");
    std::ofstream file("results/" + filename);

    if (!file.is_open()) {
        std::cout << "Cannot open file: results/" << filename << std::endl;
        return;
    }

    file << "Size,AVL,List,Open\n";

    for (int i = 0; i < count; i++) {
        file << sizes[i] << ","
             << avlAverages[i] << ","
             << listAverages[i] << ","
             << openAverages[i] << "\n";
    }

    file.close();

    std::cout << "Results saved to results/" << filename << std::endl;
}
