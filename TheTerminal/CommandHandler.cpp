#pragma once
#include "CommandHandler.h"
#include "EnvironmentManager.h"
#include "HardDrive.h"
#include <sstream>
#include <list>
#include <vector>
#include <iostream>

void CommandHandler::executeCommand(EnvironmentManager* em, std::string input)
{
	std::istringstream iss(input);
	std::string token;
	std::vector<std::string> splitCommand;

	while (std::getline(iss, token, '.')) {
		splitCommand.push_back(token);
	}
	std::cout << splitCommand[0] << "\n";
	Root* root = em->getRoot();

	if (splitCommand[0] == "TELEPORT" && !splitCommand[1].empty())
	{
		int i = 0;
		std::list<HardDrive> hds = root->getConnectdHD();
		for (auto it = hds.begin(); it != hds.end(); ++it)
		{
			if (it->getDriveName() == splitCommand[1])
			{
				em->setDiskPrompt(splitCommand[1] + ":/>");
				i = 1;
				break;
			}
		}
		if (i == 0)
		{
			em->addToCommandHistory("Not a valid drive letter!");
		}
	}
	else if(splitCommand[0] == "SCAN")
	{
		std::list<HardDrive> hds = root->getConnectdHD();
		for (auto it = hds.begin(); it != hds.end(); ++it)
		{
			em->addToCommandHistory("Drive: " + it->getDriveName() + "\t\t" + std::to_string(it->getHardDriveSize()) + "kb");
		}
		Vector2 newpromptextloc{ em->getDiskPromptTextCoord().x, em->getDiskPromptTextCoord().y + (em->getVerticleCoordJump() * (hds.size() - 2)) };

		em->setDiskPromptCoord(newpromptextloc);
	}
}