#pragma once
#include "File.h"
#include "MethodLibrary.h"

File::File(int Size, std::string FileName, std::string FileType) { size = Size; fileName = FileName; fileType = FileType; creationDate = MethodLibrary::getCurrentDateTime(); }