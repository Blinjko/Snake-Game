#include <ncurses.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <random>
#include "snake.h"
#include "food.h"
#include "game.h"

int main()
{
	initscr();
	noecho();
	keypad(stdscr, true);

	int min_y = 0;
	int min_x = 0;

	int max_y;
	int max_x;

	int score;

	getmaxyx(stdscr, max_y, max_x);

	Snake snake{'H','B',4};
	Food food{10,10,'F'};


	// subtract 1 from max x and y because ncurses is odd and 
	Game game{snake, food, stdscr, min_y, max_y-1, min_x, max_x-1};

	score = game.play();

	endwin();
	std::cout << "Your score was: " << score << std::endl;
	return 0;
}
