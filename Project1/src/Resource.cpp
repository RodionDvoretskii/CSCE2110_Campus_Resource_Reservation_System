#include "Resource.h"


// default constructor
Resource::Resource()
{
	resourceID = "";
	resourceName = "";
	resourceType = "";
	availabilityStatus = "";
}


// parameterized constructor
Resource::Resource(string resourceID, string resourceName, string resourceType, string availabilityStatus)
{
	this->resourceID = resourceID;
	this->resourceName = resourceName;
	this->resourceType = resourceType;
	this->availabilityStatus = availabilityStatus;
}

// accessors (getters)
string Resource::getResourceID() const
{
	return resourceID;
}

string Resource::getResourceName() const
{
	return resourceName;
}

string Resource::getResourceType() const
{
	return resourceType;
}

string Resource::getAvailabilityStatus() const
{
	return availabilityStatus;
}



// mutators (setters)
void Resource::setResourceID(string resourceID)
{
	this->resourceID = resourceID;
}

void Resource::setResourceName(string resourceName)
{
	this->resourceName = resourceName;
}

void Resource::setResourceType(string resourceType)
{
	this->resourceType = resourceType;
}

void Resource::setAvailabilityStatus(string availabilityStatus)
{
	this->availabilityStatus = availabilityStatus;
}


// copy constructor
Resource::Resource(const Resource& obj)
{
	this->resourceID = obj.getResourceID();
	this->resourceName = obj.getResourceName();
	this->resourceType = obj.getResourceType();
	this->availabilityStatus = obj.getAvailabilityStatus();
}


// copy assignment
Resource& Resource::operator=(const Resource& obj)
{
	if (this != &obj)
	{
		this->resourceID = obj.getResourceID();
		this->resourceName = obj.getResourceName();
		this->resourceType = obj.getResourceType();
		this->availabilityStatus = obj.getAvailabilityStatus();
	}
	
	return *this;
}