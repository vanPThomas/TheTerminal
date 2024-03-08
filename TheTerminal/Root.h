#pragma once
#include <list>
#include "HardDrive.h"

class Root
{
public:
	Root();
	void addHardDrive(HardDrive hd) { connectedHardDrives.push_back(hd); }
	std::list<HardDrive> getConnectdHD() { return connectedHardDrives; }
	std::string getRootPrompt() { return rootPrompt; }
private:
	std::list<HardDrive> connectedHardDrives{};
	std::string rootPrompt{ "/" };
};

