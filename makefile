snake: main.o functions.o
	g++ main.o functions.o -lncurses -pthread -o snake

main.o: main.cpp
	g++ -c main.cpp

functions.o: functions.cpp
	g++ -c functions.cpp

clean:
	rm *.o
