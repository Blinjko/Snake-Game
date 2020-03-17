#include <ncurses.h>
#include "functions.h" // all of the functions 
#include <vector> 
#include <mutex>
#include <thread>

int main()
{
	initscr();
	noecho();
	keypad(stdscr, true);


	std::thread t1{threadOneJob};
	t1.join();
	

	endwin();
	return 0;
}
