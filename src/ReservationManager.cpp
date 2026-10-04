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
    cout << "1. View Resources" << endl;
    cout << "2. Create Reservation" << endl;
    cout << "3. Cancel Reservation" << endl;
    cout << "4. View Waiting List" << endl;
    cout << "5. Undo Cancellation" << endl;
    cout << "6. Search Reservation" << endl;
    cout << "7. Sort Resources" << endl;
    cout << "8. Generate Report" << endl;
    cout << "9. Exit" << endl;
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

	int ReservationID;
    string StudentID, Name, ResourceID, ReservationDate;
	while (getline(fin, tmpReservationID, '|'))
	{
		ReservationID = stoi(tmpReservationID); // converts: string -> int (comes from "std")

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
				currentReservations.push_back(reservation);
			}
			else if (resource->getAvailabilityStatus() == "Unavailable")
			{
				waitingQueue.push(reservation);
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

void ReservationManager::createReservation()
{
	int ReservationID;
    string StudentID;
    string Name;
    string ResourceID;
    string ReservationDate;

    cout << "===== Enter the data for new Reservation: =====" << endl;
    cout << "Reservation ID: ";
    cin >> ReservationID;
    cin.ignore(); // to use getline without any issues
    cout << "Student ID: ";
    getline(cin, StudentID);
    cout << "Student Name: ";
    getline(cin, Name);
    cout << "Resource ID: ";
    getline(cin, ResourceID);
    cout << "Reservation Date (mm/dd/yyyy): ";
    getline(cin, ReservationDate);

    Reservation *reservationPTR = doesReservationIDExists(ReservationID);

    if (reservationPTR != nullptr) // prevents duplicate Reservation ID
    {
    	cout << "No duplicates: Reservation with such ID already exists." << endl;
    	cout << endl;
    	return;
    }

    // creates a reservation (object)
    Reservation reservation(ReservationID, StudentID, Name, ResourceID, ReservationDate);

    // inserts reservation into linked-list "currentReservations"
    currentReservations.push_back(reservation);

    cout << "Reservation Created Successfully." << endl;
    cout << endl;
}

void ReservationManager::cancelReservation() // cencels reservation - removes it from currentReservations list and stores into cancellationStack
{
	list<Reservation>::iterator it;

	int ReservationID;
	cout << "Reservation ID: ";
	cin >> ReservationID;

	Reservation *reservation = doesReservationIDExists(ReservationID);

	if (reservation == nullptr)
	{
		cout << "There is no reseservation with such ID.";
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
				break;
			}
		}
	}
}

void ReservationManager::viewWaitingList() // prints all reservations from waiting queue
{
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
	}
	else
	{
		currentReservations.push_back(cancellationStack.top()); // restores the most recently cancelled reservation
		cancellationStack.pop(); // removes the most recently cancelled reservation from cancellationStack
		cout << "Reservation Restored Successfully." << endl;
	}
	cout << endl;
}

void ReservationManager::searchReservations()  // Linear Search - O(n) Time Complexity
{
	list<Reservation>::iterator it;

	int ReservationID;
	cout << "Enter Reservation ID: ";
	cin >> ReservationID;

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
			break;
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

	int count = 1;
	for (it = currentReservations.begin(); it != currentReservations.end(); it++)
	{
		cout << "Active reservation #" << count << ":" << endl;
		cout << "________________________________________________" << endl;
		cout << "Reservation ID: " << it->getReservationID() << endl;
		cout << "Student ID: " << it->getStudentID() << endl;
		cout << "Student Name: " << it->getName() << endl;
		cout << "Reservation Date: " << it->getReservationDate() << endl;
		cout << endl;

        count++;
	}

	cout << "Resource Utilization & Waiting-List Statistics:" << endl;
	for (iter = resources.begin(); iter != resources.end(); iter++)
	{
		
		cout << "________________________________________________" << endl;
		cout << "Resource ID: " << iter->getResourceID() << endl;
        cout << "Resource Name: " << iter->getResourceName() << endl;
        cout << "Resource Type: " << iter->getResourceType() << endl;
        cout << "Resource Availability Status: " << iter->getAvailabilityStatus() << endl;
        cout << "Number of Reservations: " << getNumberOfReservations(iter->getResourceID()) << endl; // shows active reservations
        cout << "Number of Waiting Students: " << getNumberOfStudentsWaitingResource(iter->getResourceID()) << endl; // shows number of students waiting for each resource
        cout << endl;
	}

	iter = resources.begin();
	Resource first = *iter; // top 1 requested resource
	Resource second = *iter; // top 2 requested resource

	for (iter = resources.begin() + 1; iter != resources.end(); iter++)
	{
		if (getNumberOfStudentsWaitingResource(iter->getResourceID()) > getNumberOfStudentsWaitingResource(first.getResourceID()))
		{
			first = *iter;
		}
	}

	for (iter = resources.begin(); iter != resources.end(); iter++)
	{
		if (getNumberOfStudentsWaitingResource(iter->getResourceID()) < getNumberOfStudentsWaitingResource(second.getResourceID()))
		{
			second = *iter;
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
    cout << endl;

    cout << "________________________________________________" << endl;
	cout << "                    Top 2                       " << endl;
	cout << "________________________________________________" << endl;
	cout << "Resource ID: " << second.getResourceID() << endl;
    cout << "Resource Name: " << second.getResourceName() << endl;
    cout << "Resource Type: " << second.getResourceType() << endl;
    cout << "Resource Availability Status: " << second.getAvailabilityStatus() << endl;

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

Reservation* ReservationManager::doesReservationIDExists(int ReservationID) // prevents duplicate Reservation ID
{
	list<Reservation>::iterator it;

	// checks if Reservation ID is unique
	for (it = currentReservations.begin(); it != currentReservations.end(); it++)
	{
		if (it->getReservationID() == ReservationID)
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
int ReservationManager::getNumberOfReservations(string ResourceID) // returns number of reservations for specific resource
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
	list<Reservation> waitingList;

	list<Reservation>::iterator it;

	queue<Reservation> copy = waitingQueue;
	while (!copy.empty())
	{
		waitingList.push_back(copy.front());
		copy.pop();
	}

	int count = 0; // counter

	for (it = waitingList.begin(); it != waitingList.end(); it++)
	{
		if (it->getResourceID() == ResourceID)
		{
			count++;
		}
	}

	return count;
}