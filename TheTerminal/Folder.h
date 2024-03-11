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
	void setFolders(std::list<Folder*> Folders) { folders = Folders; }


	~Folder() {
		for (auto folder : folders)
		{
			delete folder;
		}
	}
private:
	std::string folderName{};
	std::list<Folder *> folders{};
	Folder* parentFolder{};
	std::string creationDate{};

};
