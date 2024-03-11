#include "File.h"
#include "MethodLibrary.h"

File::File(int Size, std::string FileContent, std::string FileType) { size = Size; fileContent = FileContent; fileType = FileType; creationDate = MethodLibrary::getCurrentDateTime(); }