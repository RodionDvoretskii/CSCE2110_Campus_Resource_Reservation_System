#include "ReservationManager.h"


int main()
{
	ReservationManager manager;

	manager.printHeader();

	string ResourcesFile = "resources.txt";
	string ReservationsFile = "reservations.txt";

	manager.loadResourcesFromFile(ResourcesFile);
	manager.loadReservationsFromFile(ReservationsFile);

	string input;
	int choice;
	while (true)
	{
		manager.printMenu();
		cin >> input;
		cout << endl;

		if (manager.isChoiceCorrect(input))
		{
			choice = stoi(input); // converts string to int

			switch (choice)
			{
				case 1:
					manager.viewResources();
					break;
				case 2:
					manager.createReservation();
					break;
				case 3:
					manager.cancelReservation();
					break;
				case 4:
					manager.viewWaitingList();
					break;
				case 5:
					manager.undoCancellation();
					manager.availabilityManager();
					break;
				case 6:
					manager.searchReservations();
					break;
				case 7:
					manager.sortResources();
					break;
				case 8:
					manager.generateReport();
					break;
				case 9:
					manager.viewCancellationHistory();
					break;
				case 10:
					manager.changeResourceAvailability();
					manager.availabilityManager();
					break;
				case 11:
					manager.viewCurrentReservations();
					break;
				case 12:
					cout << "Thank you for using \"Campus Resource Reservation System\"!" << endl;
					return 0;
				default:
					cout << "Wrong choice! try again." << endl;
					cout << endl;
					break;
			}
		}
		else
		{
			cout << "Wrong choice! try again." << endl;
			cout << endl;
		}
	}
	
	return 0;
}
