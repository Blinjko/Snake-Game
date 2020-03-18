#include "snake.h"
#include <ncurses.h>
#include <vector>
#include <thread>

int main()
{
	initscr();
	noecho();

	getch();
	endwin();
	return 0;
}
