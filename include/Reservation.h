#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation
{
    private:
        // attributes
        int ReservationID;
        string StudentID;
        string Name;
        string ResourceID;
        string ReservationDate;

    public:
        // default constructor
        Reservation();

        // parameterized constructor
        Reservation(int ReservationID, string StudentID, string Name, string ResourceID, string ReservationDate);

        // getters
        int getReservationID() const;
        string getStudentID() const;
        string getName() const;
        string getResourceID() const;
        string getReservationDate() const;

        // setters
        void setReservationID(int ReservationID);
        void setStudentID(string StudentID);
        void setName(string Name);
        void setResourceID(string ResourceID);
        void setReservationDate(string ReservationDate);
};

#endif