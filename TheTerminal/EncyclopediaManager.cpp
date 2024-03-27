#pragma once
#include "EncyclopediaManager.h"
#include "raylib.h"
#include <iostream>
#include "Character.h"

EncyclopediaManager::EncyclopediaManager() {
	Character himeko{ "Kito Himeko", "/characterpics/Himeko.png", "??", "Blessed Duality" };
	characters.push_back(himeko);
	font = LoadFont("Px437_IBM_VGA_8x14.ttf");
};

void EncyclopediaManager::runEcyclopedia()
{
	Character character = characters[0];
	std::string charPath = exePath + character.getImage();

	Texture2D characterImg = LoadTexture(charPath.c_str());
	DrawTextureEx(characterImg, {100,200}, 0.0f, 1.0f, GREEN);
	std::string charName = "Name: " + character.getName();
	std::string charBirthday = "Birthday: " + character.getBirthday();
	std::string charFirstBook = "First Book:  " + character.getFirstBook();

	DrawTextEx(font, charName.c_str(), {800, 200}, 40.0f, 1.0f, envColor);
	DrawTextEx(font, charBirthday.c_str(), { 800, 300 }, 40.0f, 1.0f, envColor);
	DrawTextEx(font, charFirstBook.c_str(), { 800, 400 }, 40.0f, 1.0f, envColor);

	//DrawText(character.getName().c_str(), 200, 200, 20, envColor);
	//UnloadTexture(characterImg);
}