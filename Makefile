main.o: main.cpp RooksPlay.h 
	g++ -std=c++17 -pthread -Wall main.cpp RooksPlay.cpp Concole.cpp -o main

