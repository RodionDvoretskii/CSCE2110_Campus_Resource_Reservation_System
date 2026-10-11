#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H


#include "Resource.h"
#include "Reservation.h"
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <iostream>
#include <fstream>


class ReservationManager
{
	private:
		list<Reservation> currentReservations; // stores all reservations whose resources have "Available" status
		vector<Resource> resources;
		stack<Reservation> cancellationStack;
		queue<Reservation> waitingQueue; // stores all reservations whose resources have "Unavailable" status
	public:
		void printHeader();
		void printMenu();
		void loadResourcesFromFile(string fileName);
		void loadReservationsFromFile(string fileName);
		void viewResources();
		void createReservation();
		void cancelReservation();
		void viewWaitingList();
		void undoCancellation();
		void searchReservations();
		void sortResources(); // sorts resources by Name using Quick Sort algorithm
		void generateReport();
		void viewCancellationHistory();
		void changeResourceAvailability();
		void viewCurrentReservations();

		// additional methods/functions
		Resource* doesResourceExistByID(string ResourceID);
		Reservation* doesReservationExistsByReservationID(string ReservationID);
		Reservation* doesReservationExistsByStudentID(string StudentID);
		Reservation* doesReservationExistsByReservationDate(string ReservationDate);
		Reservation* doesReservationExistsByResourceID(string ResourceID);

		// Quick Sort Methods
		int partition(vector<Resource> &arr, int low, int high);
		void quickSort(vector<Resource> &arr, int low, int high);

		// Resource Utilization
		int getNumberOfActiveReservations(string ResourceID);
		int getNumberOfStudentsWaitingResource(string ResourceID);

		void availabilityManager(); // reserves "Available" resources for reservations from waiting queue

		// validation
		bool isChoiceCorrect(string input);
		bool isResourceIDValid(string ResourceID);
		bool isDateValid(string date);
		bool isStudentIDValid(string StudentID);
		bool isReservationIDValid(string ReservationID);
		bool isNameValid(string Name);

		vector<int> isLeapYearOrNormal(int year);
};

#endif
