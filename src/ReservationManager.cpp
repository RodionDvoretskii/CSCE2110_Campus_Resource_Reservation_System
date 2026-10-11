#include "ReservationManager.h"

void ReservationManager::printHeader() // banner
{
	cout<<"+------------------------------------------------------+"<<endl;
	cout<<"|         Computer Science and Engineering             |"<<endl;
	cout<<"|    CSCE 2110 - Foundations of Data Structures        |"<<endl;
	cout<<"|     Rodion  rd0824   RodionDvoretskii@my.unt.edu     |"<<endl;
    cout<<"|     Arumit  ak2624   ArumitKumar@my.unt.edu          |"<<endl;
    cout<<"|     Vic     ves0058  VicScorgie@my.unt.edu           |"<<endl;
	cout<<"+------------------------------------------------------+"<<endl;
    cout << endl;
}

void ReservationManager::printMenu() // prints the menu of all possible options
{
	cout << "====== Campus Resource Reservation System ======" << endl;
    cout << "1.  View Resources" << endl;
    cout << "2.  Create Reservation" << endl;
    cout << "3.  Cancel Reservation" << endl;
    cout << "4.  View Waiting List" << endl;
    cout << "5.  Undo Cancellation" << endl;
    cout << "6.  Search Reservation" << endl;
    cout << "7.  Sort Resources" << endl;
    cout << "8.  Generate Report" << endl;
    cout << "9.  View Cancellation History" << endl;
    cout << "10. Change Resource Availability" << endl;
    cout << "11. View Current Reservations" << endl;
    cout << "12. Exit" << endl;
    cout << endl;
    cout<<"Enter Choice: ";
}

void ReservationManager::loadResourcesFromFile(string fileName)
{
	ifstream fin;
	fin.open(fileName);
	
	// validates file-opening
	if (fin.fail())
	{
		cout << "File error" << endl;
	}

	string id, name, type, status;
	while (getline(fin, id, '|'))
	{
		getline(fin, name, '|'); // reads until '|' excluding this character
		getline(fin, type, '|');
		getline(fin, status); // reads until enter/space
		
		Resource resource(id, name, type, status);
		resources.push_back(resource);
	}
	
	// close resources
	fin.close();
}

void ReservationManager::loadReservationsFromFile(string fileName)
{
	ifstream fin;
	fin.open(fileName);
	
	// validates file-opening
	if (fin.fail())
	{
		cout << "File error" << endl;
	}

	string tmpReservationID;

	string ReservationID;
    string StudentID, Name, ResourceID, ReservationDate;
	while (getline(fin, ReservationID, '|'))
	{
		getline(fin, StudentID, '|'); // reads until '|' excluding this character
		getline(fin, Name, '|');
        getline(fin, ResourceID, '|');
		getline(fin, ReservationDate); // read until enter/space
		
		// creates a reservation (object)
        Reservation reservation(ReservationID, StudentID, Name, ResourceID, ReservationDate);

        Resource *resource = doesResourceExistByID(reservation.getResourceID());

        // prevents invalid Resource ID
		if (resource == nullptr)
		{
			cout << "Resource with such ID does not exists!" << endl;
		}
		else // stores reservation (based on resource's availability status) only if resource with such ID exists
		{
			if (resource->getAvailabilityStatus() == "Available")
			{
				// debugging: reservations were not stored because of the Windows-file
				// cout << "Loaded reservation ID: " << reservation.getReservationID() << endl;
				Reservation *resID = doesReservationExistsByReservationID(ReservationID);
				Reservation *stdID = doesReservationExistsByStudentID(StudentID);

				if (resID != nullptr || stdID != nullptr)
				{
					continue; // skips
				}

				Reservation *resourceID = doesReservationExistsByResourceID(ResourceID);
				if (resourceID != nullptr)
				{
					if (resourceID->getReservationDate() == ReservationDate)
					{
						waitingQueue.push(reservation);
					}
					else
					{
						currentReservations.push_back(reservation);
					}
				}
				else
				{
					currentReservations.push_back(reservation);
				}
			}
		}
    }

    // close resources
    fin.close();
}

void ReservationManager::viewResources() // prints all resources
{
	vector<Resource>::iterator iter;

	cout << "===== Resources Info: =====" << endl;

	for (iter = resources.begin(); iter != resources.end(); iter++)
	{
		cout << "Resource ID: " << iter->getResourceID() << endl;
        cout << "Resource Name: " << iter->getResourceName() << endl;
        cout << "Resource Type: " << iter->getResourceType() << endl;
        cout << "Resource Availability Status: " << iter->getAvailabilityStatus() << endl;
        cout << endl;
	}
	cout << endl;
}

void ReservationManager::viewCurrentReservations()
{
	list<Reservation>::iterator iter;

	cout << "===== Current Reservations' Info: =====" << endl;

	int count = 1;
	for (iter = currentReservations.begin(); iter != currentReservations.end(); iter++)
	{
		cout << "Reservation #" << count << endl;
		cout << "Reservation ID: " << iter->getReservationID() << endl;
		cout << "Student ID: " << iter->getStudentID() << endl;
		cout << "Resource ID: " << iter->getResourceID() << endl;
		cout << "Student Name: " << iter->getName() << endl;
		cout << "Reservation Date: " << iter->getReservationDate() << endl;
		cout << endl;

		count++;
	}
	cout << endl;
}

void ReservationManager::createReservation()
{
	string ReservationID;
    string StudentID;
    string Name;
    string ResourceID;
    string ReservationDate;

    cin.ignore(); // to use getline without any issues

    cout << "===== Enter the data for new Reservation: =====" << endl;
    cout << "Reservation ID: ";
    getline(cin, ReservationID);
    while (!isReservationIDValid(ReservationID))
    {
    	cout << "Wrong Reservation ID. Correct format includes only 3 digits. Try again!" << endl;
    	cout << "Reservation ID: ";
    	getline(cin, ReservationID);
    }

    cout << "Student ID: ";
    getline(cin, StudentID);
    while (!isStudentIDValid(StudentID))
    {
    	cout << "Wrong Student ID. Correct format includes only 4 digits. Try again!" << endl;
    	cout << "Student ID: ";
    	getline(cin, StudentID);
    }

    cout << "Student Name: ";
    getline(cin, Name);
    while (!isNameValid(Name))
    {
    	cout << "Wrong Student Name. Correct format includes only letters, spaces, and symbols such as (\',.-). Try again!" << endl;
    	cout << "Student Name: ";
    	getline(cin, Name);
    }

    cout << "Resource ID: ";
    getline(cin, ResourceID);
    while (!isResourceIDValid(ResourceID))
    {
    	cout << "Wrong Resource ID. Correct format includes only 3 digits after capitalized \"R\". Try again!" << endl;
    	cout << "Resource ID: ";
    	getline(cin, ResourceID);
    }

    cout << "Reservation Date (mm/dd/yyyy): ";
    getline(cin, ReservationDate);
	while (!isDateValid(ReservationDate))
    {
    	cout << "Wrong Reservation Date. Correct format should look like this \"mm/dd/yyyy\". Try again!" << endl;
    	cout << "Reservation Date (mm/dd/yyyy): ";
    	getline(cin, ReservationDate);
    }

    Reservation *ResID = doesReservationExistsByReservationID(ReservationID);
    if (ResID != nullptr) // prevents duplicate Reservation ID
    {
    	cout << "No duplicates: Reservation with such Reservation ID already exists." << endl;
    	cout << endl;
    	return;
    }

    Reservation *StdID = doesReservationExistsByStudentID(StudentID);
    if (StdID != nullptr) // prevents duplicate Student ID
    {
    	cout << "No duplicates: Reservation with such Student ID already exists." << endl;
    	cout << endl;
    	return;
    }

    Resource *rsc = doesResourceExistByID(ResourceID);
    if (rsc == nullptr)
    {
    	cout << "Resource with such \"Resource ID\" does not exist. You are not able to create it." << endl;
    	cout << endl;
    	return;
    }

    if (rsc != nullptr && rsc->getAvailabilityStatus() == "Unavailable")
    {
    	cout << "Resource with such \"Resource ID\" is Unavailable. You are not able to create reservation." << endl;
    	cout << endl;
    	return;
    }

    // creates a reservation (object)
    Reservation reservation(ReservationID, StudentID, Name, ResourceID, ReservationDate);

    Reservation *rsvr = doesReservationExistsByReservationDate(ReservationDate);
    if (rsvr != nullptr && rsvr->getResourceID() == ResourceID)
    {
    	waitingQueue.push(reservation);
    	cout << "Reservation Created Successfully." << endl;
    	cout << "Added to Waiting List." << endl;
		cout << endl;
    }
    else
    {
    	currentReservations.push_back(reservation);
    	cout << "Reservation Created Successfully." << endl;
    	cout << "Added to Current Reservations." << endl;
    	cout << endl;
    }

    // Reservation *r = doesReservationExistsByResourceID(ResourceID);
    // if (rsc->getAvailabilityStatus() == "Available")
    // {
    // 	if (r != nullptr)
    // 	{
    // 		if (r->getReservationDate() == ReservationDate)///////////////////////////////////////////////////////////////////////////////////////
    // 		{
    // 			waitingQueue.push(reservation);
	// 	    	cout << "Reservation Created Successfully." << endl;
	// 	    	cout << "Added to Waiting List." << endl;
    // 			cout << endl;
    // 		}
    // 		else
    // 		{
    // 			// inserts reservation into linked-list "currentReservations"
	// 	    	currentReservations.push_back(reservation);
	// 	    	cout << "Reservation Created Successfully." << endl;
	// 	    	cout << "Added to Current Reservations." << endl;
	// 	    	cout << endl;
    // 		}
    // 	}
    // 	else
    // 	{
    // 		// inserts reservation into linked-list "currentReservations"
	//     	currentReservations.push_back(reservation);
	//     	cout << "Reservation Created Successfully." << endl;
	//     	cout << "Added to Current Reservations." << endl;
	//     	cout << endl;
    // 	}
    // }

    // Reservation *Date = doesReservationExistsByReservationDate(ReservationDate);
    // if (Date != nullptr) // prevents duplicate Reservation Date
    // {
    // 	cout << "No duplicates: Reservation with such Date already exists." << endl;
    // 	cout << endl;
    // 	return;
    // }

    // // creates a reservation (object)
    // Reservation reservation(ReservationID, StudentID, Name, ResourceID, ReservationDate);

    // if (rsc->getAvailabilityStatus() == "Available")
    // {
    // 	// inserts reservation into linked-list "currentReservations"
    // 	currentReservations.push_back(reservation);
    // 	rsc->setAvailabilityStatus("Unavailable");
    // 	cout << "Reservation Created Successfully." << endl;
    // 	cout << "Added to Current Reservations." << endl;
    // 	cout << endl;
    // }
    // else
    // {
    // 	waitingQueue.push(reservation);
    // 	cout << "Reservation Created Successfully." << endl;
    // 	cout << "Added to Waiting List." << endl;
    // 	cout << endl;
    // }
}

void ReservationManager::cancelReservation() // cencels reservation - removes it from currentReservations list and stores into cancellationStack
{
	list<Reservation>::iterator it;

	cin.ignore();

	// Reservation ID validation
	string ReservationID;
	cout << "Reservation ID: ";
    getline(cin, ReservationID);
    while (!isReservationIDValid(ReservationID))
    {
    	cout << "Wrong Reservation ID. Correct format includes only 3 digits. Try again!" << endl;
    	cout << "Reservation ID: ";
    	getline(cin, ReservationID);
    }

	Reservation *reservation = doesReservationExistsByReservationID(ReservationID);

	if (reservation == nullptr)
	{
		cout << "There is no reseservation with such ID. Nothing to cancel.";
		cout << endl;
	}
	else
	{
		for (it = currentReservations.begin(); it != currentReservations.end(); it++)
		{
			if (it->getReservationID() == ReservationID)
			{
				cancellationStack.push(*it);
				currentReservations.erase(it);
				cout << "Added to cancellation history." << endl;
				cout << endl;
				return;
			}
		}

		queue<Reservation> copy = waitingQueue;
		queue<Reservation> adjusted;

		Reservation rsv;
		while (!copy.empty())
		{
			rsv = copy.front();
			copy.pop();

			if (rsv.getReservationID() == ReservationID)
			{
				cancellationStack.push(rsv);
			}
			else
			{
				adjusted.push(rsv);
			}
		}

		waitingQueue = adjusted;

		cout << "Added to cancellation history." << endl;
		cout << endl;
	}
}

void ReservationManager::viewWaitingList() // prints all reservations from waiting queue
{
	if (waitingQueue.empty())
	{
		cout << "Waiting List is Empty." << endl;
		cout << endl;
		return;
	}

	cout << "===== Waiting Queue Reservations' Info: =====" << endl;

	int count = 1;
	queue<Reservation> copy = waitingQueue;

	while (!copy.empty())
	{
		cout << "Position in Queue #" << count << endl;
		cout << "Reservation ID: " << copy.front().getReservationID() << endl;
		cout << "Student ID: " << copy.front().getStudentID() << endl;
		cout << "Resource ID: " << copy.front().getResourceID() << endl;
		cout << "Student Name: " << copy.front().getName() << endl;
		cout << "Reservation Date: " << copy.front().getReservationDate() << endl;
		cout << endl;

		copy.pop();
		count++;
	}
	cout << endl;
}

void ReservationManager::undoCancellation()
{
	if (cancellationStack.empty()) // handles empty stack
	{
		cout << "Cancellation Stack is empty. Cannot restore." << endl;
		cout << endl;
	}
	else
	{
		Reservation reser = cancellationStack.top();

		Resource *rsc = doesResourceExistByID(reser.getResourceID());
		if (rsc != nullptr && rsc->getAvailabilityStatus() == "Available")
		{
			Reservation *rsvr = doesReservationExistsByReservationDate(reser.getReservationDate());
		    if (rsvr != nullptr && rsvr->getResourceID() == reser.getResourceID())
		    {
		    	cancellationStack.pop(); // removes the most recently cancelled reservation from cancellationStack
		    	waitingQueue.push(reser);
		    	cout << "Reservation Restored Successfully." << endl;
		    	cout << "Added to Waiting List." << endl;
				cout << endl;
		    }
		    else
		    {
		    	cancellationStack.pop(); // removes the most recently cancelled reservation from cancellationStack
		    	currentReservations.push_back(reser);
		    	cout << "Reservation Restored Successfully." << endl;
		    	cout << "Added to Current Reservations." << endl;
		    	cout << endl;
		    }
		}
		else
		{
			cout << "Resource with such \"Resource ID\" is Unavailable. You are not able to restore this reservation." << endl;
			cout << endl;	
		}
	}
}

void ReservationManager::searchReservations()  // Linear Search - O(n) Time Complexity
{
	list<Reservation>::iterator it;

	cin.ignore();
	
	string ReservationID;
	cout << "Enter Reservation ID: ";
	getline(cin, ReservationID);
    while (!isReservationIDValid(ReservationID))
    {
    	cout << "Wrong Reservation ID. Correct format includes only 3 digits. Try again!" << endl;
    	cout << "Reservation ID: ";
    	getline(cin, ReservationID);
    }

	for (it = currentReservations.begin(); it != currentReservations.end(); it++)
	{
		if (it->getReservationID() == ReservationID)
		{
			cout << "===== Reservation is found: ======" << endl;
			cout << "Reservation ID: " << it->getReservationID() << endl;
			cout << "Student ID: " << it->getStudentID() << endl;
			cout << "Resource ID: " << it->getResourceID() << endl;
			cout << "Student Name: " << it->getName() << endl;
			cout << "Reservation Date: " << it->getReservationDate() << endl;
			cout << endl;
			return;
		}
	}

	queue<Reservation> copy = waitingQueue;
	if (!copy.empty())
	{
		Reservation r;
		while (!copy.empty())
		{
			r = copy.front();
			if (r.getReservationID() == ReservationID)
			{
				cout << "===== Reservation is found: ======" << endl;
				cout << "Reservation ID: " << r.getReservationID() << endl;
				cout << "Student ID: " << r.getStudentID() << endl;
				cout << "Resource ID: " << r.getResourceID() << endl;
				cout << "Student Name: " << r.getName() << endl;
				cout << "Reservation Date: " << r.getReservationDate() << endl;
				cout << endl;
				return;
			}
		}
	}

	cout << "Reservation with such ID does not exists." << endl;
	cout << endl;
}

void ReservationManager::sortResources() // implements Quick Sort algorithm (sorts resources by Name)
{
	quickSort(resources, 0, resources.size() - 1);
}

void ReservationManager::generateReport()
{
	vector<Resource>::iterator iter;
	list<Reservation>::iterator it;

	cout << "___________________________________________________________" << endl;
	cout << "                          Report:                          " << endl;
	cout << "___________________________________________________________" << endl;
	cout << endl;

	if (resources.empty())
	{
		cout << "No resources. Vector is Empty." << endl;
		cout << endl;
	}

	cout << "_______________________________________________" << endl;
	cout << "Resource Utilization & Waiting-List Statistics:" << endl;
	cout << "_______________________________________________" << endl;
	for (iter = resources.begin(); iter != resources.end(); iter++)
	{
		
		cout << "________________________________________________" << endl;
		cout << "Resource ID: " << iter->getResourceID() << endl;
        cout << "Resource Name: " << iter->getResourceName() << endl;
        cout << "Resource Type: " << iter->getResourceType() << endl;
        cout << "Resource Availability Status: " << iter->getAvailabilityStatus() << endl;
        cout << "Number of Active Reservations: " << getNumberOfActiveReservations(iter->getResourceID()) << endl; // shows active reservations
        cout << "Number of Waiting Students: " << getNumberOfStudentsWaitingResource(iter->getResourceID()) << endl; // shows number of students waiting for each resource
        cout << endl;
	}

	iter = resources.begin();
	Resource first = *iter; // top 1 requested resource
	Resource second; // top 2 requested resource

	int tmp1;
	int tmpFirst = getNumberOfActiveReservations(first.getResourceID()) + getNumberOfStudentsWaitingResource(first.getResourceID());
	for (iter = resources.begin() + 1; iter != resources.end(); iter++)
	{
		tmp1 = getNumberOfActiveReservations(iter->getResourceID()) + getNumberOfStudentsWaitingResource(iter->getResourceID()); // number of students requested thus resource (active+waiting)
		if (tmp1 > tmpFirst)
		{
			first = *iter;
			tmpFirst = tmp1;
		}
	}

	int tmp2;
	int tmpSecond = -1;
	for (iter = resources.begin(); iter != resources.end(); iter++)
	{
		tmp2 = getNumberOfActiveReservations(iter->getResourceID()) + getNumberOfStudentsWaitingResource(iter->getResourceID()); // number of students requested thus resource (active+waiting)
		if (tmp2 > tmpSecond && iter->getResourceID() != first.getResourceID())
		{
			second = *iter;
			tmpSecond = tmp2;
		}
	}

	cout << "Most requested resources (top 2):" << endl;
	cout << "________________________________________________" << endl;
	cout << "                    Top 1                       " << endl;
	cout << "________________________________________________" << endl;
	cout << "Resource ID: " << first.getResourceID() << endl;
    cout << "Resource Name: " << first.getResourceName() << endl;
    cout << "Resource Type: " << first.getResourceType() << endl;
    cout << "Resource Availability Status: " << first.getAvailabilityStatus() << endl;
    cout << "Number of Requests: "<< getNumberOfActiveReservations(first.getResourceID()) + getNumberOfStudentsWaitingResource(first.getResourceID()) << endl;
    cout << endl;

    cout << "________________________________________________" << endl;
	cout << "                    Top 2                       " << endl;
	cout << "________________________________________________" << endl;
	cout << "Resource ID: " << second.getResourceID() << endl;
    cout << "Resource Name: " << second.getResourceName() << endl;
    cout << "Resource Type: " << second.getResourceType() << endl;
    cout << "Resource Availability Status: " << second.getAvailabilityStatus() << endl;
    cout << "Number of Requests: "<< getNumberOfActiveReservations(second.getResourceID()) + getNumberOfStudentsWaitingResource(second.getResourceID()) << endl;
	cout << endl;
}

void ReservationManager::viewCancellationHistory()
{
	stack<Reservation> copy = cancellationStack;

	if (copy.empty())
	{
		cout << "Cancellation History is Empty." << endl;
		cout << endl;
		return;
	}

	int count = 1;

	cout << "===== Cancellation History: =====" << endl;
	while (!copy.empty())
	{
		cout << "Position in Stack #" << count << endl;
		cout << "Reservation ID: " << copy.top().getReservationID() << endl;
		cout << "Student ID: " << copy.top().getStudentID() << endl;
		cout << "Resource ID: " << copy.top().getResourceID() << endl;
		cout << "Student Name: " << copy.top().getName() << endl;
		cout << "Reservation Date: " << copy.top().getReservationDate() << endl;
		cout << endl;

		copy.pop();
		count++;
	}

	cout << endl;
}

void ReservationManager::changeResourceAvailability()
{
	cin.ignore();

	string ResourceID;
	cout << "Resource ID: ";
    getline(cin, ResourceID);
    while (!isResourceIDValid(ResourceID))
    {
    	cout << "Wrong Resource ID. Correct format includes only 3 digits after capitalized \"R\". Try again!" << endl;
    	cout << "Resource ID: ";
    	getline(cin, ResourceID);
    }

	Resource *rsc = doesResourceExistByID(ResourceID);

	if (rsc == nullptr)
	{
		cout << "Resource with such Resource ID is not found." << endl;
	}
	else
	{
		if (rsc->getAvailabilityStatus() == "Available")
		{
			cout << "Resource status was changed from \"" << rsc->getAvailabilityStatus() << "\" to \"Unavailable\"" << endl;
			rsc->setAvailabilityStatus("Unavailable");
		}
		else if (rsc->getAvailabilityStatus() == "Unavailable")
		{
			cout << "Resource status was changed from \"" << rsc->getAvailabilityStatus() << "\" to \"Available\"" << endl;
			rsc->setAvailabilityStatus("Available");
		}
	}

	cout << endl;
}

// additional methods/functions
Resource* ReservationManager::doesResourceExistByID(string ResourceID) // checks if such Resource ID exists
{
	vector<Resource>::iterator iter;

	// checks if resource with such name exists
	for (iter = resources.begin(); iter != resources.end(); iter++)
	{
		if (iter->getResourceID() == ResourceID)
		{
			return &(*iter);
		}
	}
	return nullptr;
}

Reservation* ReservationManager::doesReservationExistsByReservationID(string ReservationID) // prevents duplicate Reservation ID
{
	list<Reservation>::iterator it;

	// checks if Reservation ID is unique
	for (it = currentReservations.begin(); it != currentReservations.end(); it++) // searches within the list "currentReservations"
	{
		if (it->getReservationID() == ReservationID)
		{
			return &(*it);
		}
	}

	Reservation *rsv;
	queue<Reservation> copy = waitingQueue;

	if (!copy.empty())
	{
		while (!copy.empty()) // searches within waiting list
		{
			rsv = &copy.front();
			if (rsv->getReservationID() == ReservationID)
			{
				return rsv;
			}
			copy.pop();
		}
	}

	return nullptr;
}

Reservation* ReservationManager::doesReservationExistsByStudentID(string StudentID)
{
	list<Reservation>::iterator it;

	// checks if Reservation ID is unique
	for (it = currentReservations.begin(); it != currentReservations.end(); it++) // searches within the list "currentReservations"
	{
		if (it->getStudentID() == StudentID)
		{
			return &(*it);
		}
	}

	Reservation *rsv;
	queue<Reservation> copy = waitingQueue;

	if (!copy.empty())
	{
		while (!copy.empty()) // searches within waiting list
		{
			rsv = &copy.front();
			if (rsv->getStudentID() == StudentID)
			{
				return rsv;
			}
			copy.pop();
		}
	}

	return nullptr;
}

Reservation* ReservationManager::doesReservationExistsByReservationDate(string ReservationDate)
{
	list<Reservation>::iterator it;

	// checks if Reservation ID is unique
	for (it = currentReservations.begin(); it != currentReservations.end(); it++) // searches within the list "currentReservations"
	{
		if (it->getReservationDate() == ReservationDate)
		{
			return &(*it);
		}
	}

	Reservation *rsv;
	queue<Reservation> copy = waitingQueue;

	if (!copy.empty())
	{
		while (!copy.empty()) // searches within waiting list
		{
			rsv = &copy.front();
			if (rsv->getReservationDate() == ReservationDate)
			{
				return rsv;
			}
			copy.pop();
		}
	}

	return nullptr;
}

Reservation* ReservationManager::doesReservationExistsByResourceID(string ResourceID)
{
	list<Reservation>::iterator it;

	// checks if Reservation ID is unique
	for (it = currentReservations.begin(); it != currentReservations.end(); it++) // searches within the list "currentReservations"
	{
		if (it->getResourceID() == ResourceID)
		{
			return &(*it);
		}
	}

	return nullptr;
}

// Quick Sort Methods
int ReservationManager::partition(vector<Resource> &arr, int low, int high)
{
	Resource pivot = arr[high];

	int i = low - 1;

	for (int j = low; j <= high - 1; j++)
	{
		// ASCII number of letter that comes earlier is less, than number of letter that comes after
		if (arr[j].getResourceName() < pivot.getResourceName())
		{
			i++;
			swap(arr[i], arr[j]); // built-in method
		}
	}

	swap(arr[i + 1], arr[high]);
	return i + 1;
}

void ReservationManager::quickSort(vector<Resource> &arr, int low, int high)
{
	if (low < high)
	{
		int indexOfPivot = partition(arr, low, high);

		quickSort(arr, low, indexOfPivot - 1);
		quickSort(arr, indexOfPivot + 1, high);
	}
}

// Resource Utilization
int ReservationManager::getNumberOfActiveReservations(string ResourceID) // returns number of reservations for specific resource
{
	list<Reservation>::iterator it;

	int count = 0; // counter

	for (it = currentReservations.begin(); it != currentReservations.end(); it++)
	{
		if (it->getResourceID() == ResourceID)
		{
			count++;
		}
	}

	return count;
}

int ReservationManager::getNumberOfStudentsWaitingResource(string ResourceID) // returns number of students waiting for specific resource
{	
	if (waitingQueue.empty())
	{
		return 0;
	}
	
	queue<Reservation> copy = waitingQueue;

	int count = 0; // counter
	
	Reservation r;
	while (!copy.empty())
	{
		r = copy.front();
		if (r.getResourceID() == ResourceID)
		{
			count++;
		}
		copy.pop();
	}

	return count;
}

void ReservationManager::availabilityManager()
{
	list<Reservation>::iterator it;
	vector<Resource>::iterator iter;

	queue<Reservation> copy = waitingQueue;
	queue<Reservation> changed;

	for (iter = resources.begin(); iter != resources.end(); iter++)
	{
		if (iter->getAvailabilityStatus() == "Unavailable")
		{
			for (it = currentReservations.begin(); it != currentReservations.end();)
			{
				if (iter->getResourceID() == it->getResourceID())
				{
					cancellationStack.push(*it);
					it = currentReservations.erase(it);
				}
				else
				{
					it++;
				}
			}

			Reservation res;
			if (!copy.empty())
			{
				while (!copy.empty())
				{
					res = copy.front();
					copy.pop();

					if (res.getResourceID() != iter->getResourceID())
					{
						changed.push(res);
					}
					else
					{
						cancellationStack.push(res);
					}
				}
				waitingQueue = changed;
			}
		}
	}
}

vector<int> ReservationManager::isLeapYearOrNormal(int year)
{
	vector<int> normal = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // [0] amount of days in Janaury - [11] amount of days in December (for normal year)
	vector<int> leap = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return leap;
	}

	return normal;
}

// validation
bool ReservationManager::isChoiceCorrect(string input) // choice vailadtion
{
	char c;

	for (int i = 0; i < (int) input.length(); i++)
	{
		c = input[i];

		if (!isdigit(c))
		{
			return false;
		}
	}

	return true;
}

bool ReservationManager::isResourceIDValid(string ResourceID)
{
	char c1, c2, c3, c4;
	if (ResourceID.size() == 4)
	{
		c1 = ResourceID[0];
		c2 = ResourceID[1];
		c3 = ResourceID[2];
		c4 = ResourceID[3];
		if (c1 == 'R' && isdigit(c2) && isdigit(c3) && isdigit(c4))
		{
			return true;
		}
	}

	return false;
}

bool ReservationManager::isDateValid(string date)
{
	string m;
	string d;
	string y;

	int month;
	int day;
	int year;

	if (date.length() == 10)
	{
		char dv1, dv2; // dividers
		dv1 = date[2];
		dv2 = date[5];

		char m1, m2;
		m1 = date[0];
		m2 = date[1];

		char d1, d2;
		d1 = date[3];
		d2 = date[4];

		char y1, y2, y3, y4;
		y1 = date[6];
		y2 = date[7];
		y3 = date[8];
		y4 = date[9];

		if (dv1 == '/' && dv2 == '/' && isdigit(m1) && isdigit(m2) && isdigit(d1) && isdigit(d2) && isdigit(y1) && y1 != '0' && isdigit(y2) && isdigit(y3) && isdigit(y4))
		{
			// month 01 - 12
			if (m1 == '0')
			{
				m += m2;
				month = stoi(m);
			}
			else
			{
				m += m1;
				m += m2;
				month = stoi(m);
			}

			// days - depend on the year type (leap or normal), ex: 01 - 31
			if (d1 == '0')
			{
				d += d2;
				day = stoi(d);
			}
			else
			{
				d += d1;
				d += d2;
				day = stoi(d);
			}

			// year
			y += y1;
			y += y2;
			y += y3;
			y += y4;

			year = stoi(y);

			vector<int> monthsAndDays = isLeapYearOrNormal(year);

			if ((1 <= month && month <= 12) && (1 <= day && day <= monthsAndDays.at(month - 1)) && year >= 2026)
			{
				return true;
			}
		}	
	}

	return false;
}

bool ReservationManager::isStudentIDValid(string StudentID)
{
	char d1, d2, d3, d4;
	if (StudentID.size() == 4)
	{
		d1 = StudentID[0];
		d2 = StudentID[1];
		d3 = StudentID[2];
		d4 = StudentID[3];

		if (isdigit(d1) && isdigit(d2) && isdigit(d3) && isdigit(d4))
		{
			return true;
		}
	}

	return false;
}

bool ReservationManager::isReservationIDValid(string ReservationID)
{
	char d1, d2, d3;
	if (ReservationID.size() == 3)
	{
		d1 = ReservationID[0];
		d2 = ReservationID[1];
		d3 = ReservationID[2];

		if (isdigit(d1) && isdigit(d2) && isdigit(d3))
		{
			return true;
		}
	}

	return false;
}

bool ReservationManager::isNameValid(string Name)
{
	char d;
	for (int i = 0; i < (int) Name.length(); i++)
	{
		d = Name[i];
		if (!isalpha(d) && d != '\'' && d != '-' && d != ' ' && d != '.')
		{
			return false;
		}
	}

	return true;
}
