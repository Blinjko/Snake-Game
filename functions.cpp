#include "functions.h"
#include <ncurses.h>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <random>


struct Segment // Segment object to represent each body segment of the snake
{
	int y;
	int x;

	Direction nextMove;
	Direction lastMove;

	char symbol; // what the snake body segment will be printed as

	Segment(int i_y, int i_x, char i_symbol, Direction i_nextMove) : // constructor to set all values
		y{i_y}, x{i_x}, symbol{i_symbol}, nextMove{i_nextMove}
	{
	}

	Segment() : y{0}, x{0}, symbol{'D'}, nextMove{RIGHT}, lastMove{RIGHT} // default constructor
	{
	}

};



Direction getInput() // gets input from keyboard and returns a proper direction if an arrow key is pressed, if another key is pressed, them MAX_DIRECTIONS is returned
{
	int input = getch();

	switch(input)
	{
		case 258: // down arrow key
			return DOWN;

		case 259: // up arrow key
			return UP;

		case 260: // right arrow key
			return LEFT;

		case 261: // left arrow key
			return RIGHT;

		default: // an arrow key was not pressed
			return MAX_DIRECTIONS;
	}


}


void printSnake(std::vector<Segment> &snake) // function to print the snake, automatically clears and refreshs the screen
{
	clear();
	for(Segment s: snake)
	{
		mvprintw(s.y, s.x, "%c", s.symbol);
	}
	move(0,0); // move the cursor to 0,0 to make the sceen look more clean
	refresh();
}

void moveSegment(Segment &s) // moves a singular segment based upon its next movement
{
	switch(s.nextMove)
	{
		case DOWN:
			++s.y;
			break;

		case UP:
			--s.y;
			break;

		case RIGHT:
			++s.x;
			break;

		case LEFT:
			--s.x;
			break;
	}
}


void moveSegments(std::vector<Segment> &snake) // function to move all of a snakes segments in their appropriate directions
{
	for(std::size_t i{0}; i<snake.size(); ++i)
	{
		if(i == 0) // the snakes head
		{
			moveSegment(snake.at(i)); // move the head
			snake.at(i).lastMove = snake.at(i).nextMove; // set the last move to the move just made
		}
		else
		{
			moveSegment(snake.at(i)); // move the segment
			snake.at(i).lastMove = snake.at(i).nextMove; // set the last move to the move just made
			snake.at(i).nextMove = snake.at(i-1).lastMove; // set the next move to the previous segments last move
		}
	}
}

bool findCollision(std::vector<Segment> &snake) // finds out if the snake has collided with itself, if it has return true, if not return false
{
	Segment& head = snake.at(0); // get the head

	for(std::size_t i{1}; i<snake.size(); ++i)
	{
		if((head.x == snake.at(i).x) && (head.y == snake.at(i).y)) // checks if snake head coordinates are the same as a body parts
		{
			return true;
		}
	}
	return false; // no collision found 
}



void threadTwoJob(std::vector<Segment> &s, std::mutex &m)
{
	Direction input;
	bool collision = false;
	while(!collision)
	{
		input = getInput();

		std::lock_guard<std::mutex> lock{m}; // lock the mutex so a race condition does not happen

		//check if the gotten direction is opposite current one, causing the snake to go inside itself
		if(input == RIGHT && s.at(0).lastMove == LEFT)
		{
			collision = findCollision(s);
		}
		else if(input == LEFT && s.at(0).lastMove == RIGHT)
		{
			collision = findCollision(s);
		}
		else if(input == UP && s.at(0).lastMove == DOWN)
		{
			collision = findCollision(s);
		}
		else if(input == DOWN && s.at(0).lastMove == UP)
		{
			collision = findCollision(s);
		}
		else if(input == MAX_DIRECTIONS)
		{
			collision = findCollision(s);
		}
		else
		{
			s.at(0).nextMove = input;
			collision = findCollision(s);
		}


	}
}


void threadOneJob() // function to take care of moving the snake
{
	std::mutex snakeMutex; // mutex for threads

	std::vector<Segment> snake = {Segment(0,4,'H',RIGHT)}; // element 0 head of the snake

	// snake body segments
	snake.resize(4); // resize once for efficiency
	snake.at(1) = Segment(0,3,'B',RIGHT); // body segment 2
	snake.at(2) = Segment(0,2,'B',RIGHT); // body segment 3
	snake.at(3) = Segment(0,1,'B',RIGHT); // body segment 4

	bool collision = false; // true if snake has collided with itself, false if snake has not collided with itself


	std::thread t2{threadTwoJob, std::ref(snake), std::ref(snakeMutex)};

	while(!collision) // while the snake has not collided with itself
	{
		//snake.at(0).nextMove = getInput(snake.at(0).nextMove); // get the heads direction based on user input, visit getInput() for more info
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); // have t1 sleep for 200 milliseconds

		std::lock_guard<std::mutex> lock{snakeMutex};
		moveSegments(snake);
		printSnake(snake);
		collision = findCollision(snake);
	}

	t2.join(); // thread 2 joins before t1 terminates
}
