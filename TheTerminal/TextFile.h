#pragma once
#include "File.h"

class TextFile : public File
{
public:
	using File::File;

private:
	std::string content{ "test" };

};