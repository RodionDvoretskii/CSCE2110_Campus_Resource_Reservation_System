#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>


bool ResourceManager::loadFromFile(string fileName)
{
	ifstream fin;
	fin.open(fileName);
	
	if (fin.fail())
	{
		cout << "File error" << endl;
		return false;
	}
	string line, id, name, type, status;
	
	while (getline(fin, id, '|'))
	{
		getline(fin, name, '|');
		getline(fin, type, '|');
		getline(fin, status);
		
		if (!status.empty() && status[status.size() - 1] == '\r')
		{
			status.erase(status.size() - 1);
		}
		
		// reading failed (e.g. empty line at the end): stop
		if (fin.fail())
		{
			break;
		}
		
		Resource resource(id, name, type, status);
		resources.push_back(resource);
	}
	
	fin.close();
	return true;
}


int ResourceManager::findResource(string resourceID) const
{
	for (int i = 0; i < (int)resources.size(); i++)
	{
		if (resources[i].getResourceID() == resourceID)
		{
			return i;
		}
	}
	return -1;
}


int ResourceManager::getCount() const
{
	return resources.size();
}


Resource& ResourceManager::getResource(int index)
{
	return resources[index];
}


bool ResourceManager::setAvailability(string resourceID, string status)
{
	int index = findResource(resourceID);
	
	if (index == -1)
	{
		return false;   // no such resource
	}
	
	resources[index].setAvailabilityStatus(status);
	return true;
}


void ResourceManager::displayAll() const
{
	cout << left << setw(8) << "ID" << setw(24) << "Name" << setw(24) << "Type" << "Status" << endl;
	
	for (int i = 0; i < (int)resources.size(); i++)
	{
		cout << left << setw(8) << resources[i].getResourceID()
		     << setw(24) << resources[i].getResourceName()
		     << setw(24) << resources[i].getResourceType()
		     << resources[i].getAvailabilityStatus() << endl;
	}
}


void ResourceManager::displayAvailability() const
{
	int availableCount = 0;
	
	cout << left << setw(8) << "ID" << setw(24) << "Name" << "Status" << endl;
	
	for (int i = 0; i < (int)resources.size(); i++)
	{
		cout << left << setw(8) << resources[i].getResourceID()
		     << setw(24) << resources[i].getResourceName()
		     << resources[i].getAvailabilityStatus() << endl;
		
		if (resources[i].getAvailabilityStatus() == "Available")
		{
			availableCount++;
		}
	}
	
	cout << endl << availableCount << " of " << resources.size() << " resources available." << endl;
}