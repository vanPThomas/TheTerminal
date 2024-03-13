#pragma once
#include <list>
#include "HardDrive.h"
#include <boost/serialization/list.hpp>
class HardDrive;

namespace boost {
	namespace serialization {
		// Define std::list<HardDrive*>
		template<class Archive>
		void serialize(Archive& ar, std::list<HardDrive*>& list, const unsigned int version)
		{
			ar& list;
		}
	}
}

class Root
{
public:
	Root();
	void addHardDrive(HardDrive *hd) { connectedHardDrives.push_back(hd); }
	std::list<HardDrive *> getConnectdHD() { return connectedHardDrives; }
	std::string getRootPrompt() { return rootPrompt; }

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& connectedHardDrives;
	}

private:
	std::list<HardDrive *> connectedHardDrives{};
	std::string rootPrompt{ "#" };
};

