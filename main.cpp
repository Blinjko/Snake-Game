#include "snake.h"
#include <ncurses.h>
#include <vector>
#include <thread>
#include "food.h"

int main()
{
	initscr();
	noecho();

	getch();
	endwin();
	return 0;
}
