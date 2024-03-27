#pragma once
#include <string>
class Character
{
public:
	Character(std::string Name, std::string Image, std::string Birthday, std::string FirstBook);
	std::string getName() { return name; }
	std::string getImage() { return image; }
	std::string getBirthday() { return birthday; }
	std::string getFirstBook() { return firstBook; }
private:
	std::string image;
	std::string name;
	std::string birthday;
	std::string firstBook;
};

