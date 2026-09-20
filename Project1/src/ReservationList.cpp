#include "ReservationList.h"
#include <iostream>
#include <iomanip>


ReservationList::ReservationList()
{
	head = nullptr;
	tail = nullptr;
	count = 0;
}


// deletes all elements when the list is destroyed
ReservationList::~ReservationList()
{
	Node* current = head;
	while (current != nullptr)
	{
		// remember the next one BEFORE deleting
		Node* nextNode = current->next;
		delete current;
		current = nextNode;
	}
}


void ReservationList::insertReservation(Reservation r)
{
	// Node constructor stores r and sets next = NULL
	Node* newNode = new Node(r);
	
	// empty list: the new node is both first and last
	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		// attach after the last node
		tail->next = newNode;
		tail = newNode;
	}
	count++;
}


bool ReservationList::removeReservation(int reservationID, Reservation& removed)
{
	Node* previous = nullptr;
	Node* current = head;
	
	// walk through the list until we find the ID
	while (current != nullptr && current->data.get_ReservationID() != reservationID)
	{
		previous = current;
		current = current->next;
	}
	
	// reached the end: not found
	if (current == nullptr)
	{
		return false;
	}
	
	// give the removed reservation back (it goes to the stack)
	removed = current->data;
	
	// removing the first node
	if (previous == nullptr)
	{
		head = current->next;
	}
	else
	{
		// skip over the node
		previous->next = current->next;
	}
	
	// removed the last node: move tail back
	if (current == tail)
	{
		tail = previous;
	}
	
	delete current;
	count--;
	return true;
}


bool ReservationList::findReservation(int reservationID) const
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data.get_ReservationID() == reservationID)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}


int ReservationList::getCount() const
{
	return count;
}


void ReservationList::displayReservations() const
{
	if (head == nullptr)
	{
		cout << "No active reservations." << endl;
		return;
	}
	
	cout << left << setw(8) << "ResID" << setw(12) << "StudentID" << setw(22) << "Student Name"
	     << setw(10) << "Resource" << "Date" << endl;
	
	Node* current = head;
	while (current != nullptr)
	{
		cout << left << setw(8) << current->data.get_ReservationID()
		     << setw(12) << current->data.get_StudentID()
		     << setw(22) << current->data.get_Name()
		     << setw(10) << current->data.get_ResourceID()
		     << current->data.get_ReservationDate() << endl;
		current = current->next;
	}
}