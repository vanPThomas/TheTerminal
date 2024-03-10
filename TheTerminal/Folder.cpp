#pragma once
#include "Folder.h"
#include <string>

Folder::Folder(std::string FolderName, Folder* ParentFolder) { folderName = FolderName; parentFolder = ParentFolder; }