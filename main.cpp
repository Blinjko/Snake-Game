#include "snake.h"
#include <ncurses.h>
#include <vector>

int main()
{
	initscr();
	noecho();

	Snake snake('H', 'B', 4);

	snake.print(stdscr);

	getch();
	endwin();
	return 0;
}
