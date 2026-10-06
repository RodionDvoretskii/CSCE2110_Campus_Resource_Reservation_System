# Project 1: Campus Resource Reservation System (CSCE 2110)
Universities manage a variety of resources every day, including study rooms, tutoring appointments, laptops, calculators, and laboratory equipment. Students frequently request access to these resources, and administrators must efficiently manage reservations, waiting lists, cancellations, and usage reports.

In this project, our team developed a Campus Resource Reservation System that allows users to reserve campus resources, manage waiting lists, track reservation history, and generate reports.

This project aims to apply object-oriented programming and fundamental data structures to solve a real-world problem.

**Features**

1. View Resources - Displays all resources in the system and shows the resource ID, name, type, and availability status

2. Create Reservations - Allows the student to enter information to make a new reservation; it checks that the resource exists and is available, checks that the reservation ID is not in use, and stores the reservation in the active reservation list. 

3. Cancel Reservation - Searches for the reservation using its ID, removes the reservation from the list, and stores the canceled reservation in a stack so it can be restored

4. View Waiting List - Displays reservations currently in the waiting queue. Shows each student's position in the queue.

5. Undo Cancellation - Displays all the reservations that are currently in the waiting queue, using a stack that follows a LIFO structure

6. Search Reservation - Searches the active reservation list using a reservation ID. Uses a linear search.

7. Sort Resources - Sorts the listed resources alphabetically by resource name. Uses the Quick Sort algorithm. 

8. Generate Reports - Displays active reservations and resource utilization information, shows the number of reservations for each resource and the number of students waiting for each resource. It also displays the two most requested resources.

**Data Structures Used**

1. Vector
2. Linked List
3. Queue
4. Stack

**Files**

data-
  reservations.txt
  resources.txt
include- 
  Reservation.h
  ReservationManager.h
  Resource.h
src-
  Main.cpp
  Reservation.cpp
  ReservationManager.cpp
  Resource.cpp
Makefile
README.md

To Compile It Write:
1) make
2) ./project1Milestone.exe
