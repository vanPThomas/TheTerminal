#pragma once
#include <string>
#include <vector>
#include "EnvironmentManager.h"
class CommandHandler
{
public:
	static void executeCommand(EnvironmentManager* em, std::string input);
	static void triggerTeleport(EnvironmentManager* em, Root* root, std::vector<std::string> splitCommand);
	static void triggerExit();
	static void triggerHelp(EnvironmentManager* em);
	static void triggerScan(EnvironmentManager* em, Root* root);
	static void triggerShift(EnvironmentManager* em, std::vector<std::string> splitCommand);

private:
	
};

