#pragma once
#include <string>
#include <list>
#include "Folder.h"

class HardDrive
{
public:
	HardDrive(std::string DriveName, int size);
	void addFolder(Folder *folder) { folders.push_back(folder); }
	int getHardDriveSize() { return size; }
	std::string getDriveName() { return driveName; }
	std::list<Folder*> getFolders() { return folders; }
private:
	std::string driveName{};
	int size{};
	std::list<Folder *> folders{};
};

