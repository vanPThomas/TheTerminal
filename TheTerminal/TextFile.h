#pragma once
#include "File.h"
class TextFile : public File
{
public:
	using File::File;
	
	std::string content{ "test" };
private:
};

