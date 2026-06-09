

#include "Random.h"

// Seed the generator once and reuse it across the whole program.
std::random_device Random::rd;
std::mt19937 Random::gen(Random::rd());

int Random::generateRandomInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(Random::gen);
}
