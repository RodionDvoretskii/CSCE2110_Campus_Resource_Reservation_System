#ifndef RESERVATIONLIST_H
#define RESERVATIONLIST_H


#include "Reservation.h"
#include "Node.h"

class ReservationList
{
	private:
		// first element (NULL if list is empty)
		Node* head;   
		// last element
		Node* tail;
		// number of reservations in the list
		int count;
		// copying a list is not allowed (prevents double delete)
		ReservationList(const ReservationList& obj);
		ReservationList& operator=(const ReservationList& obj);
	public:
		ReservationList();
		~ReservationList();
		
		// adds reservation at the end of the list
		void insertReservation(Reservation r);
		
		// removes reservation with this ID; puts a copy into 'removed'. false if not found
		bool removeReservation(int reservationID, Reservation& removed);
		
		// true if a reservation with this ID exists
		bool findReservation(int reservationID) const;
		
		// number of active reservations
		int getCount() const;
		
		// goes through the whole list and prints every reservation
		void displayReservations() const;
};


#endif