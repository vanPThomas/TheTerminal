#pragma once
#include "Folder.h"
#include <string>
#include "MethodLibrary.h"

Folder::Folder(std::string FolderName, Folder* ParentFolder) { folderName = FolderName; parentFolder = ParentFolder; creationDate = MethodLibrary::getCurrentDateTime(); }