#include "Reservation.h"

// default constructor
Reservation::Reservation()
{
    ReservationID = 0;
    StudentID = "";
    Name = "";
    ResourceID = "";
    ReservationDate = "";
}


// parameterized constructor
Reservation::Reservation(int ReservationID, string StudentID, string Name, string ResourceID, string ReservationDate)
{
    this->ReservationID = ReservationID;
    this->StudentID = StudentID;
    this->Name = Name;
    this->ResourceID = ResourceID;
    this->ReservationDate = ReservationDate;
}


// getters
int Reservation::getReservationID() const
{
    return ReservationID;
}

string Reservation::getStudentID() const
{
    return StudentID;
}

string Reservation::getName() const
{
    return Name;
}

string Reservation::getResourceID() const
{
    return ResourceID;
}

string Reservation::getReservationDate() const
{
    return ReservationDate;
}


// setters
void Reservation::setReservationID(int ReservationID)
{
    this->ReservationID = ReservationID;
}

void Reservation::setStudentID(string StudentID)
{
    this->StudentID = StudentID;
}

void Reservation::setName(string Name)
{
    this->Name = Name;
}

void Reservation::setResourceID(string ResourceID)
{
    this->ResourceID = ResourceID;
}

void Reservation::setReservationDate(string ReservationDate)
{
    this->ReservationDate = ReservationDate;
}