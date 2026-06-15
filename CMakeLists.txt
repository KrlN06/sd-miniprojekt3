cmake_minimum_required(VERSION 3.20)

project(Projekt_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Projekt_3
    src/Benchmark.cpp
    src/BenchmarkSaver.cpp
    src/main.cpp
    src/HashTableChainingAVL.cpp
    src/HashTableChainingList.cpp
    src/HashTableOpenAddressing.cpp
    src/Interface.cpp
    src/Random.cpp
    src/Timer.cpp
)

target_include_directories(Projekt_3 PRIVATE include)
