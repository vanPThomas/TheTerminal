#pragma once
#include "MethodLibrary.h"
#include <iostream>
#include <random>
#include <ctime>
#include <iomanip>
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <unistd.h>
#include <limits.h>
#endif

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

#include <string>

std::string MethodLibrary::getExecutablePath() {
    std::string path;

#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    path = buffer;
    size_t lastSeparator = path.find_last_of("\\");
    if (lastSeparator != std::string::npos)
        path = path.substr(0, lastSeparator);

    // Replace backslashes with forward slashes
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '\\')
            path[i] = '/';
    }
#elif __linux__
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        path = buffer;
        size_t lastSeparator = path.find_last_of("/");
        if (lastSeparator != std::string::npos)
            path = path.substr(0, lastSeparator);
    }
#endif

    return path;
}

