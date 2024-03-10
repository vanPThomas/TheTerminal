#pragma once
#include "MethodLibrary.h"
#include <iostream>
#include <random>
#include <ctime>
#include <iomanip>

int MethodLibrary::getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(rng);
}

std::string MethodLibrary::getCurrentDateTime()
{
    std::time_t currentTime;
    std::time(&currentTime);

    std::tm localTime;
    localtime_s(&localTime, &currentTime);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
    std::string currentDate(buffer);

    return currentDate;
}
