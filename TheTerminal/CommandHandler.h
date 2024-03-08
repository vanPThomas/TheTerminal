#pragma once
#include <string>
#include "EnvironmentManager.h"
class CommandHandler
{
public:
	static void executeCommand(EnvironmentManager* em, std::string input);
};

