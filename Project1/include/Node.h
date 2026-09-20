#ifndef NODE_H
#define NODE_H

#include "Reservation.h"

class Node
{
	public:
		Reservation data;
		Node* next;
		
		// default constructor
		Node();
		
		// parameterized constructor
		Node(Reservation reservation);
};


#endif