#pragma once
#include <string>

class MethodLibrary
{
public:
	static int getRandomNumber(int min, int max);
	static std::string getCurrentDateTime();
	static std::string getExecutablePath();
};

