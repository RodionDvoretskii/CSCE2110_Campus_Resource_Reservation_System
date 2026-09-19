#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <iostream>
#include string

using namespace std;

struct WaitingNode
{
    int studentID;
    string studentName;
    string resourceID;
    string date;
    WaitingNode* next;
};

class WaitingList
{
private:
    WaitingNode* front;
    WaitingNode* rear;

public:
    WaitingList();

    void addStudent(int studentID, string studentName, string resourceID, string date);

    void removeStudent();

    void display();

    bool isEmpty();
};

#endif
