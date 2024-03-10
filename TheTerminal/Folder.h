#pragma once
#include <list>
#include <string>

class Folder
{
public:
	Folder(std::string FolderName, Folder *ParentFolder);
	std::string getFolderName(){ return folderName; }
	Folder* getParentFolder() { return parentFolder; }
	std::list<Folder*> getFolders(){ return folders; }
	void addFolderToFolders(Folder* folder) { folders.push_back(folder); }
	std::string getCreationDate() { return creationDate; }
private:
	std::string folderName{};
	std::list<Folder *> folders{};
	Folder* parentFolder{};
	std::string creationDate{};

};
