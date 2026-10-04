#ifndef RESOURCE_H // header guard
#define RESOURCE_H

#include <string>
using namespace std; // useful for string

class Resource
{
	private:
		// attributes
		string resourceID;
		string resourceName;
		string resourceType;
		string availabilityStatus;
	public:
		// default constructor
		Resource();
		// parameterized constructor
		Resource(string resourceID, string resourceName, string resourceType, string availabilityStatus);
		
		// getters/accessors
		string getResourceID() const;
		string getResourceName() const;
		string getResourceType() const;
		string getAvailabilityStatus() const;
		
		// setters/mutators
		void setResourceID(string resourceID);
		void setResourceName(string resourceName);
		void setResourceType(string resourceType);
		void setAvailabilityStatus(string availabilityStatus);
};


#endif