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
	static void triggerShiftUp(EnvironmentManager* em);
	static void triggerRoot(EnvironmentManager* em);
	static void triggerCreate(EnvironmentManager* em, std::vector<std::string> splitCommand);
	static void triggerCrush(EnvironmentManager* em, std::vector<std::string> splitCommand);
	static void triggerWipe(EnvironmentManager* em);
	static void runEncyclopedia(EnvironmentManager* em);
	static void triggerRun(EnvironmentManager* em, std::vector<std::string> splitCommand);


private:
	
};

