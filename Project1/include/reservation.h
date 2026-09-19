#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>
using namespace std;

class Reservation
{
private:
    // All the required data members for the reservation!
    int ReservationID;
    int StudentID;
    int ResourceID;
    string Name;
    string ReservationDate;

public:
    Reservation();                              // Default constructor
    Reservation(int, int, int, string, string); // fully parametrized construtor
    //~Reservation();

    // Here we have the getters and setters for all the data members!
    int get_ReservationID() const;
    void set_ReservationID(int);

    int get_StudentID() const;
    void set_StudentID(int);

    int get_ResourceID() const;
    void set_ResourceID(int);

    string get_Name() const;
    void set_Name(string);

    string get_ReservationDate() const;
    void set_ReservationDate(string);
};
#endif