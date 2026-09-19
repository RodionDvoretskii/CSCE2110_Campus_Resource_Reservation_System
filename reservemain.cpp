#include "reservation.h"
#include <iostream>
#include <string>
#include <list>
#include <stack>
using namespace std;

void printInfo(Reservation* ptr){
    cout<<"Reservation ID is : "<<ptr->get_ReservationID()<<endl
                        <<"Student ID is : "<<ptr->get_StudentID()<<endl
                        <<"Resource ID is : "<< ptr->get_ResourceID()<<endl
                        <<"Name is : "<<ptr->get_Name()<<endl
                        <<"Reservation Date is : "<< ptr->get_ReservationDate()<<endl
                        <<"-------------------------------------"<<endl;
}

int main()
{

    Reservation *reserveptr;// creating a Reservation class pointer to store addressed of instances
    list<Reservation*>currentReservations; //This is a temp list to check if my
                                            // Reservation mangmemenr works!
                                            //also this is a doubly linked list!
    stack<Reservation*>cancellationStack;
    /*This is temp stack which will let us iterate over the stack withour loosing the original elements*/
    stack<Reservation*>tempstack = cancellationStack;


    while(true)
    {
        int choice = 0;
        cout << "===== Campus Resource Reservation System =====" << endl;

        cout << "1. Create reservations\n"
             << "2. Display active reservations\n"
             << "3. Cancel reservation\n"
             << "4. Restore the most recent cancelled reservation\n"
             << "5. Display cancellation history\n"
             <<"6. Exit" << endl;
        cin >> choice;

        if (choice == 1)
        {
            char validate;
            int ReservationID;
            int StudentID;
            int ResourceID;
            string Name;
            string ReservationDate;

            cout << "Enter the Reservation ID : " << endl;
            cin >> ReservationID;

            cout << "Enter the Student ID : " << endl;
            cin >> StudentID;

            cout << "Enter the Resource ID : " << endl;
            cin >> ResourceID;

            cin.ignore();

            cout << "Enter student Name : " << endl;
            getline(cin, Name);

            cout << "Enter the Reservation Date : " << endl;
            getline(cin, ReservationDate);

            cout << "Validate y/n?" << endl;
            cin >> validate;

            if (validate == 'y')
            {
                reserveptr = new Reservation(ReservationID,
                                              StudentID,
                                              ResourceID,
                                              Name,
                                              ReservationDate);
                //Here I'm storing pointer address to this object instance to the 
                //doubly linked list, in linked list it only contains the address\
                //not the data!
                currentReservations.push_back(reserveptr);
                cout<<"Size right now is "<< currentReservations.size()<<endl;
            }
            else{
                cout<<"please start over!"<<endl;
            }
        }

        if(choice == 2){
            cout<<"Displaying Data below!"<<endl;

                for(auto ptr: currentReservations){
                        printInfo(ptr);
                }
        }
        if(choice == 3){
            char cancel;
            cout<<"Do you want to cancel the most recent Reservation? y/n "<<endl;
            cin>>cancel;

            if(cancel == 'y'){
                cout<<"Cancelling reservation for : "<<currentReservations.back()->get_Name()<<endl;
                cancellationStack.push(currentReservations.back());
                currentReservations.pop_back();
            }
            else{
                cout<<"Try again"<<endl;
                continue;
            }
        }
        if(choice == 4){
            char cancel;
            cout<<"Do you want to restore the most recent cancelled Reservation? y/n "<<endl;
            cin>>cancel;
            if(cancellationStack.empty()){
                cout<<"Cancellation stack is empty right now!"<<endl;
            }
            if(cancel == 'y'){
                currentReservations.push_back(cancellationStack.top());
                cout<<"Success Student : "<<currentReservations.back()->get_Name()<<endl;
                cancellationStack.pop();
            }
            else{
                cout<<"Try again"<<endl;
                continue;
            }

        }
        if(choice == 5){
            cout<<"Displaying Cancellation history!"<<endl;
            tempstack = cancellationStack;
            if(tempstack.empty()){
                cout<<"Cancellation list is currently empty!"<<endl;
                continue;
            }
            
            while(!tempstack.empty()){
                Reservation* ptr = tempstack.top();
                printInfo(ptr);
                tempstack.pop();
            }
        }
        if(choice == 6){
            cout<<"Thank you for using this program!"<<endl;
            break;
        }
    }

    for(auto ptr : currentReservations){
        delete ptr;
    }
    currentReservations.clear();

}