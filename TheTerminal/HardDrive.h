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
	void setFolders(std::list<Folder *> Folders) { folders = Folders; }
	void addFileToFiles(File* file) { files.push_back(file); }
	std::list<File*> getFiles() { return files; }
	void setFiles(std::list<File*> Files) { files = Files; }

private:
	std::string driveName{};
	int size{};
	std::list<Folder *> folders{};
	std::list<File*> files{};

};

