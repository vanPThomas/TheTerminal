#pragma once
#include<string>
class File
{
public:
	File(int size, std::string FileContent, std::string FileType);
	int getFileSize() { return size; }
	std::string getCreationDate() { return creationDate; }
	std::string getFileContent() { return fileContent; }
	std::string getFileType() { return fileType; }
private:
	int size{};
	std::string creationDate{};
	std::string fileContent{};
	std::string fileType{};
};

