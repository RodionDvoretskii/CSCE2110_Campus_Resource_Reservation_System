#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H


#include "Resource.h"
#include <vector>


class ResourceManager
{
	public:
		bool loadFromFile(string fileName);
		int findResource(string resourceID) const;
		int getCount() const;
		Resource& getResource(int index);
		bool setAvailability(string resourceID, string status);
		void displayAll() const;
		void displayAvailability() const;
	private:
		vector<Resource> resources;
};


#endif