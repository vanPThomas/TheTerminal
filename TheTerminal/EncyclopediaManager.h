#pragma once
#include "raylib.h"
#include "MethodLibrary.h"
#include "Character.h"
#include <string>
#include <list>
#include <vector>

class EncyclopediaManager
{
public:
	EncyclopediaManager();
	void runEcyclopedia();

private:
	//Texture2D character;
	std::string exePath = MethodLibrary::getExecutablePath();
	std::vector<Character> characters{};
	Font font{};
	Color envColor = GREEN;
};

