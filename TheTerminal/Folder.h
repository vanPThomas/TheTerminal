#pragma once
#include <list>
#include <string>

class Folder
{
public:
	Folder(std::string FolderName);
	std::string getFolderName(){ return folderName; }
private:
	std::string folderName{};
	// std::list<Folder> folders{};

};
