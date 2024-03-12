#pragma once
#include<string>
class File
{
public:
	File(int size, std::string FileName, std::string FileType);
	int getFileSize() { return size; }
	std::string getCreationDate() { return creationDate; }
	std::string getFileType() { return fileType; }
	std::string getFileName() { return fileName; }
private:
	int size{};
	std::string creationDate{};
	std::string fileType{};
	std::string fileName{};
};

