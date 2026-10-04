project1Milestone.exe: Resource.o Reservation.o ReservationManager.o Main.o 
	g++ Resource.o Reservation.o ReservationManager.o Main.o -o project1Milestone.exe
Resource.o: Resource.cpp Resource.h
	g++ -Wall -c Resource.cpp
Reservation.o: Reservation.cpp Reservation.h
	g++ -Wall -c Reservation.cpp
ReservationManager.o: ReservationManager.cpp ReservationManager.h Resource.h Reservation.h
	g++ -Wall -c ReservationManager.cpp		
Main.o: Main.cpp ReservationManager.h Resource.h Reservation.h
	g++ -Wall -c Main.cpp
clean:
	rm *.o project1Milestone.exe