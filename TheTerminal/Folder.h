#pragma once
#include <list>
#include <string>
#include "File.h"

class Folder
{
public:
	Folder(std::string FolderName, Folder *ParentFolder);
	std::string getFolderName(){ return folderName; }
	Folder* getParentFolder() { return parentFolder; }
	std::list<Folder*> getFolders(){ return folders; }
	void addFolderToFolders(Folder* folder) { folders.push_back(folder); }
	std::string getCreationDate() { return creationDate; }
	void setFolders(std::list<Folder*> Folders) { folders = Folders; }
	void addFileToFiles(File* file) { files.push_back(file); }
	std::list<File*> getFiles() { return files; }
	void setFiles(std::list<File*> Files) { files = Files;  }

	~Folder() {
		for (auto folder : folders)
		{
			delete folder;
		}
		for (auto file : files)
		{
			delete file;
		}
	}

private:
	std::string folderName{};
	std::list<Folder *> folders{};
	Folder* parentFolder{};
	std::string creationDate{};
	std::list<File*> files{};

};
