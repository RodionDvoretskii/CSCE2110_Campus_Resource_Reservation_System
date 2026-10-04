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

		// additional methods/functions
		Resource* doesResourceExistByID(string ResourceID);
		Reservation* doesReservationIDExists(int ReservationID);

		// Quick Sort Methods
		int partition(vector<Resource> &arr, int low, int high);
		void quickSort(vector<Resource> &arr, int low, int high);

		// Resource Utilization
		int getNumberOfReservations(string ResourceID);
		int getNumberOfStudentsWaitingResource(string ResourceID);
};

#endif