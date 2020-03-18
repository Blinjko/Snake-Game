snake: main.o snake.o food.o
	g++ main.o snake.o food.o -lncurses -pthread -o snake

main.o: main.cpp
	g++ -c main.cpp

snake.o:
	g++ -c snake.cpp

food.o:
	g++ -c food.cpp

clean:
	rm *.o
