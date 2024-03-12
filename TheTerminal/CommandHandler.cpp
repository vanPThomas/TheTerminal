#pragma once
#include "CommandHandler.h"
#include "EnvironmentManager.h"
#include "HardDrive.h"
#include <sstream>
#include <list>
#include <vector>
#include <iostream>
#include "TextFile.h"
#include "MethodLibrary.h"

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

	if (splitCommand[0] == "TELEPORT")
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
	else if (splitCommand[0] == "SHIFT")
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
	else if (splitCommand[0] == "CREATE")
	{
		triggerCreate(em, splitCommand);
	}
	else if (splitCommand[0] == "CRUSH")
	{
		triggerCrush(em, splitCommand);
	}
	else
	{
		em->addToCommandHistory("Invalid Command!");
	}
}

void CommandHandler::triggerTeleport(EnvironmentManager* em, Root* root, std::vector<std::string> splitCommand)
{
	if (splitCommand.size() < 2)
	{
		em->addToCommandHistory("ERROR: Bad command!");
		return;
	}
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
	"TELEPORT.[NODE LETTER]\t\t\t Switch to a different storage Node.",
	"SHIFT.[COLLECTION NAME]\t\t\tShift to a different Collection.",
	"SHIFTUP\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tShift up one Collection.",
	"CREATE.[TYPE].[NAME]\t\t\t\t\t\tCreate a Collection or File.",
	"CRUSH.[TYPE].[NAME]\t\t\t\t\t\t\tDestroy a Collection or File.",
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
				em->addToCommandHistory((*it)->getFolderName() + "\t\t\t" + (*it)->getCreationDate() + "\t\t\t<COLLECTION>");
			}
		}
		if (!hd->getFiles().empty())
		{
			std::list<File*> files = hd->getFiles();
			for (auto it = files.begin(); it != files.end(); ++it)
			{
				em->addToCommandHistory((*it)->getFileName() + "\t\t\t" + (*it)->getCreationDate() + "\t\t\t<" + (*it)->getFileType() + ">" + "\t\t\t" + std::to_string((*it)->getFileSize()) + "kb");
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
				em->addToCommandHistory((*it)->getFolderName() + "\t\t\t" + (*it)->getCreationDate() + "\t\t\t<COLLECTION>");
			}
		}
		if (!currentFolder->getFiles().empty())
		{
			std::list<File*> files = currentFolder->getFiles();
			for (auto it = files.begin(); it != files.end(); ++it)
			{
				em->addToCommandHistory((*it)->getFileName() + "\t\t\t" + (*it)->getCreationDate() + "\t\t\t<" + (*it)->getFileType() + ">" + "\t\t\t" + std::to_string((*it)->getFileSize()) + "kb");
			}
		}
	}

}

void CommandHandler::triggerShift(EnvironmentManager *em, std::vector<std::string> splitCommand)
{
	if (splitCommand.size() < 2)
	{
		em->addToCommandHistory("ERROR: Bad command!");
		return;
	}
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
			//em->addToCommandHistory((*it)->getFolderName());
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
			//em->addToCommandHistory((*it)->getFolderName());
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

void CommandHandler::triggerCreate(EnvironmentManager* em, std::vector<std::string> splitCommand)
{
	if (splitCommand.size() < 3)
	{
		em->addToCommandHistory("ERROR: Bad command!");
		return;
	}
	if (splitCommand[1] == "COLLECTION")
	{
		if (em->getCurrentFolderLocation() != NULL)
		{
			for (auto folder : em->getCurrentFolderLocation()->getFolders())
			{
				if (folder->getFolderName() == splitCommand[2])
				{
					em->addToCommandHistory("ERROR: A collection with that name already exists");
					return;
				}
			}
			Folder* folder = new Folder(splitCommand[2], em->getCurrentFolderLocation());
			em->getCurrentFolderLocation()->addFolderToFolders(folder);
		}
		else if (em->getCurrentDriveLocation() != NULL)
		{
			for (auto folder : em->getCurrentDriveLocation()->getFolders())
			{
				if (folder->getFolderName() == splitCommand[2])
				{
					em->addToCommandHistory("ERROR: A collection with that name already exists");
					return;
				}
			}
			Folder* folder = new Folder(splitCommand[2], NULL);
			em->getCurrentDriveLocation()->addFolder(folder);
		}
		else
		{
			em->addToCommandHistory("ERROR: Can't create a collection in the root");
		}
	}
	else if (splitCommand[1] == "TEXT")
	{
		if (em->getCurrentFolderLocation() != NULL)
		{
			for (auto file : em->getCurrentFolderLocation()->getFiles())
			{
				if (file->getFileName() == splitCommand[2])
				{
					em->addToCommandHistory("ERROR: A text file with that name already exists");
					return;
				}
			}
			File* file = new TextFile(MethodLibrary::getRandomNumber(100, 1000), splitCommand[2], "TEXT");
			em->getCurrentFolderLocation()->addFileToFiles(file);
		}
		else if (em->getCurrentDriveLocation() != NULL)
		{
			for (auto file : em->getCurrentDriveLocation()->getFiles())
			{
				if (file->getFileName() == splitCommand[2])
				{
					em->addToCommandHistory("ERROR: A text file with that name already exists");
					return;
				}
			}
			File* file = new TextFile(MethodLibrary::getRandomNumber(100, 1000), splitCommand[2], "TEXT");
			em->getCurrentDriveLocation()->addFileToFiles(file);
		}
		else
		{
			em->addToCommandHistory("ERROR: Can't create a collection in the root");
		}
	}
}

void CommandHandler::triggerCrush(EnvironmentManager* em, std::vector<std::string> splitCommand)
{
	if (splitCommand.size() < 3)
	{
		em->addToCommandHistory("ERROR: Bad command!");
		return;
	}
	if (splitCommand[1] == "COLLECTION")
	{
		std::list<Folder*> folders{};
		bool folderPresent = false;
		if (em->getCurrentFolderLocation() != NULL)
		{
			for (auto folder : em->getCurrentFolderLocation()->getFolders())
			{
				if (folder->getFolderName() == splitCommand[2])
				{
					delete folder;
					folderPresent = true;
				}
				else
				{
					folders.push_back(folder);
				}
			}
			if (!folderPresent)
			{
				em->addToCommandHistory("ERROR: No Collection with that name found.");
			}
			em->getCurrentFolderLocation()->setFolders(folders);
		}
		else if (em->getCurrentDriveLocation() != NULL)
		{
			for (auto folder : em->getCurrentDriveLocation()->getFolders())
			{
				if (folder->getFolderName() == splitCommand[2])
				{
					delete folder;
					folderPresent = true;
				}
				else
				{
					folders.push_back(folder);
				}
			}
			if (!folderPresent)
			{
				em->addToCommandHistory("ERROR: No Collection with that name found.");
			}
			em->getCurrentDriveLocation()->setFolders(folders);
		}
		else
		{
			em->addToCommandHistory("ERROR: Can't delete in Root.");
		}
	}
	else if (splitCommand[1] == "TEXT")
	{
		std::list<File*> files{};
		bool filePresent = false;
		if (em->getCurrentFolderLocation() != NULL)
		{
			for (auto file : em->getCurrentFolderLocation()->getFiles())
			{
				if (file->getFileName() == splitCommand[2] && file->getFileType() == splitCommand[1])
				{
					delete file;
					filePresent = true;
				}
				else
				{
					files.push_back(file);
				}
			}
			if (!filePresent)
			{
				em->addToCommandHistory("ERROR: Not a valid crush command.");
			}
			em->getCurrentFolderLocation()->setFiles(files);
		}
		else if (em->getCurrentDriveLocation() != NULL)
		{
			for (auto file : em->getCurrentDriveLocation()->getFiles())
			{
				if (file->getFileName() == splitCommand[2] && file->getFileType() == splitCommand[1])
				{
					delete file;
					filePresent = true;
				}
				else
				{
					files.push_back(file);
				}
			}
			if (!filePresent)
			{
				em->addToCommandHistory("ERROR: Not a valid crush command.");
			}
			em->getCurrentDriveLocation()->setFiles(files);
		}
		else
		{
			em->addToCommandHistory("ERROR: Can't delete in Root.");
		}
	}
}