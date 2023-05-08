project: main.o Simulator.o CardDeck.o Player.o  Card.o 
	g++ -o project Simulator.o CardDeck.o Card.o Player.o main.o
main.o:main.cpp Simulator.h
	g++ -c main.cpp	
Simulator.o:Simulator.cpp Simulator.h
	g++ -c Simulator.cpp
CardDeck.o:CardDeck.cpp CardDeck.h
	g++ -c CardDeck.cpp
Player.o:Player.cpp Player.h
	g++ -c Player.cpp
Card.o:Card.cpp Card.h
	g++ -c Card.cpp
clean: 
	rm *.o project 
