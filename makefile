snake: main.o snake.o food.o game.o
	g++ main.o snake.o food.o game.o -lncurses -pthread -o snake

main.o: main.cpp
	g++ -c main.cpp

snake.o: snake.cpp
	g++ -c snake.cpp

food.o: food.cpp
	g++ -c food.cpp

game.o: game.cpp
	g++ -c game.cpp

clean:
	rm *.o
