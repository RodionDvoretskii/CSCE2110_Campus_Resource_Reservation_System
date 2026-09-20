#include "Node.h"

// default constructor
Node::Node()
{
	next = nullptr;
}
		
// parameterized constructor
Node::Node(Reservation reservation)
{
	data = reservation;
	next = nullptr;
}