#include "WaitingList.h"

WaitingList::WaitingList()
{
    front = nullptr;
    rear = nullptr;
}
bool WaitingList::isEmpty()
{
    return front == nullptr;
}
void WaitingList::addStudent(int studentID, string studentName, string resourceID, string date)
{
    WaitingNode* newNode = new WaitingNode;

    newNode->studentID = studentID;
    newNode->studentName = studentName;
    newNode->resourceID = resourceID;
    newNode->date = date;
    newNode->next = nullptr;
    
    if (front == nullptr)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}
void WaitingList::removeStudent()
{
    if(front == nullprt)
    {
        cout << "Waiting list is empty." <<endl;
        return;
    }
    WaitingNode* temp = front;
    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete temp;
}

void WaitingList::display()
{
    WaitingNode* current = front;
    if (current == nullptr)
    {
        cout << "Waiting list is empty." << endl;
        return;
    }
    while (current != nullptr)
    {
        cout << "Student ID: " << current->studentID << endl;
        cout << "Student Name: " << current->studentName << endl;
        cout << "Resource ID: " << current->resourceID << endl;
        cout << "Date: " << current->date << endl;
        cout << endl;
        current = current->next;
    }
}
