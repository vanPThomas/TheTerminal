#pragma once
#include "MethodLibrary.h"
#include <iostream>
#include <random>

int MethodLibrary::getRandomNumber(int min, int max) {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 rng(rd());

    // Define the distribution
    std::uniform_int_distribution<int> distribution(min, max);

    // Generate and return a random number
    return distribution(rng);
}