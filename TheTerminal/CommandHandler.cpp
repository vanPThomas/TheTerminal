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
		triggerTeleport(em, root, splitCommand);
	}
	else if(splitCommand[0] == "SCAN")
	{
		triggerScan(em, root);
	}
	else if (splitCommand[0] == "EXIT")
	{
		triggerExit();
	}
	else if (splitCommand[0] == "HELP")
	{
		triggerHelp(em);
	}
	else if (splitCommand[0] == "SHIFT" && !splitCommand[1].empty())
	{
		triggerShift(em, splitCommand);
	}
	else if (splitCommand[0] == "SHIFTUP")
	{
		triggerShiftUp(em);
	}
	else if (splitCommand[0] == "ROOT")
	{
		triggerRoot(em);
	}
	else
	{
		em->addToCommandHistory("Invalid Command!");
	}
}

void CommandHandler::triggerTeleport(EnvironmentManager* em, Root* root, std::vector<std::string> splitCommand)
{
	int i = 0;
	std::list<HardDrive *> hds = root->getConnectdHD();
	for (auto it = hds.begin(); it != hds.end(); ++it)
	{
		if ((*it)->getDriveName() == splitCommand[1])
		{
			em->setDiskPrompt(splitCommand[1] + "#>");
			i = 1;
			em->setCurrentDriveLocation((*it));
			em->setCurrentFolderLocation(NULL);
			std::list<std::string> currentPath{};
			em->setCurrentPath(currentPath);
			break;
		}
	}
	if (i == 0)
	{
		em->addToCommandHistory("Not a valid node letter!");
	}
}

void CommandHandler::triggerExit()
{
	CloseWindow();
	exit(0);
}

void CommandHandler::triggerHelp(EnvironmentManager *em)
{
	std::list<std::string> commands = {
	"",
	"TELEPORT.[NODE LETTER]\t\t\t Switch to a different storage node.",
	"SHIFT.[COLLECTION NAME]\t\t\tShift to a different Collection.",
	"SHIFTUP\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tShift up one Collection."
	"SCAN\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tScan the current node or collection.",
	"EXIT\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tShut down HoloGeisha OS.",
	"HELP\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tShow all commands.",
	"ROOT\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tGo to the system Root.",
	""
	};
	for (auto it = commands.begin(); it != commands.end(); ++it)
	{
		em->addToCommandHistory(*it);
	}
}

void CommandHandler::triggerScan(EnvironmentManager *em, Root *root)
{
	if (em->getCurrentDriveLocation() == NULL)
	{
		std::list<HardDrive *> hds = root->getConnectdHD();
		for (auto it = hds.begin(); it != hds.end(); ++it)
		{
			em->addToCommandHistory("Node: " + (*it)->getDriveName() + "\t\t" + std::to_string((*it)->getHardDriveSize()) + "kb");
		}
		Vector2 newpromptextloc{ em->getDiskPromptTextCoord().x, em->getDiskPromptTextCoord().y + (em->getVerticleCoordJump() * (hds.size() - 2)) };

		em->setDiskPromptCoord(newpromptextloc);
	}
	else if (em->getCurrentFolderLocation() == NULL)
	{
		HardDrive* hd = em->getCurrentDriveLocation();
		std::cout << hd->getHardDriveSize() << "\n";
		
		if (!hd->getFolders().empty())
		{
			std::list<Folder *> folders = hd->getFolders();
			for (auto it = folders.begin(); it != folders.end(); ++it)
			{
				em->addToCommandHistory((*it)->getFolderName() + "\t\t\t" + (*it)->getCreationDate());
			}
		}
	}
	else 
	{
		Folder* currentFolder = em->getCurrentFolderLocation();
		if (!currentFolder->getFolders().empty())
		{
			std::list<Folder*> folders = currentFolder->getFolders();
			for (auto it = folders.begin(); it != folders.end(); ++it)
			{
				em->addToCommandHistory((*it)->getFolderName() + "\t\t\t" + (*it)->getCreationDate());
			}
		}
	}

}

void CommandHandler::triggerShift(EnvironmentManager *em, std::vector<std::string> splitCommand)
{
	int i = 0;
	std::list<Folder*> folders{};
	if (em->getCurrentDriveLocation() == NULL)
	{
		em->addToCommandHistory("Please use TELEPORT to select a node first.");
	}
	else if (em->getCurrentFolderLocation() == NULL)
	{
		folders = em->getCurrentDriveLocation()->getFolders();
		for (auto it = folders.begin(); it != folders.end(); ++it)
		{
			em->addToCommandHistory((*it)->getFolderName());
			if ((*it)->getFolderName() == splitCommand[1])
			{
				em->setDiskPrompt(em->getCurrentDriveLocation()->getDriveName() + "#" + splitCommand[1] + "=>");
				i = 1;
				em->setCurrentFolderLocation((*it));
				std::list<std::string> currentPath = em->getCurrentPath();
				currentPath.push_back(splitCommand[1]);
				em->setCurrentPath(currentPath);
				break;
			}
		}
	}
	else
	{
		Folder* folder = em->getCurrentFolderLocation();
		folders = folder->getFolders();
		std::string promptText{ em->getCurrentDriveLocation()->getDriveName()};
		std::list<std::string> currentPath = em->getCurrentPath();
		for (const std::string& pathElement : currentPath) 
		{
			promptText += "#";
			promptText += pathElement;
		}
		for (auto it = folders.begin(); it != folders.end(); ++it)
		{
			em->addToCommandHistory((*it)->getFolderName());
			if ((*it)->getFolderName() == splitCommand[1])
			{
				promptText += "#";
				promptText += splitCommand[1];
				promptText += "=>";
				em->setDiskPrompt(promptText);
				i = 1;
				em->setCurrentFolderLocation((*it));
				std::list<std::string> currentPath = em->getCurrentPath();
				currentPath.push_back(splitCommand[1]);
				em->setCurrentPath(currentPath);
				break;
			}
		}
	}

	if (i == 0)
	{
		em->addToCommandHistory("Not a valid collection name!");
	}
}

void CommandHandler::triggerShiftUp(EnvironmentManager* em)
{
	std::list<Folder*> folders{};
	if (em->getCurrentDriveLocation() == NULL)
	{
		em->addToCommandHistory("Please use TELEPORT to select a node.");
	}
	else if (em->getCurrentFolderLocation() == NULL)
	{
		em->addToCommandHistory("No parent collection found.");
	}
	else
	{
		Folder* currentFolder = em->getCurrentFolderLocation();
		Folder* parentFolder = currentFolder->getParentFolder();

		//folders = parentFolder->getFolders();
		em->setCurrentFolderLocation(parentFolder);
		if (parentFolder != NULL)
		{
			std::string promptText{ em->getCurrentDriveLocation()->getDriveName() };
			std::list<std::string> currentPath = em->getCurrentPath();
			currentPath.pop_back();
			em->setCurrentPath(currentPath);
			for (const std::string& pathElement : currentPath)
			{
				promptText += "#";
				promptText += pathElement;
			}
			promptText += "=>";
			em->setDiskPrompt(promptText);
		}
		else
		{
			std::string promptText{ em->getCurrentDriveLocation()->getDriveName() };
			promptText += "#>";
			em->setDiskPrompt(promptText);
		}

	}
}

void CommandHandler::triggerRoot(EnvironmentManager* em)
{
	em->setCurrentDriveLocation(NULL);
	em->setCurrentFolderLocation(NULL);
	std::list<std::string> currentPath{};
	em->setCurrentPath(currentPath);
	em->setDiskPrompt("#");
}