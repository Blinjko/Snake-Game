#include <ncurses.h>
#include <chrono>
#include <vector>
#include <thread>

enum Direction // directions that Segments of the snake can move in
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX_DIRECTIONS,
};

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

	Segment() : y{0}, x{0}, symbol{'D'}, nextMove{LEFT}, lastMove{LEFT} // default constructor
	{
	}

};

// forward declarations
void snake(); // fucntion that moves the snake
Direction getInput(Direction head_nextMove); // gets input and depending on arrow key pressed it returns the corresponding Direction type
void printSnake(std::vector<Segment> &snake); // prints the snake to the screen
void moveSegments(std::vector<Segment> &snake); // after input is gotten and the heads direction is changed, call this to move the body segments appropriately
void moveSegment(Segment &s); // moves a singular segment based upon its next movement
bool findCollision(std::vector<Segment> &snake); // looks to see if the snakes head has hit one of the body segments, if so return true, else return false

int main()
{
	initscr();
	noecho();
	keypad(stdscr, true);

	std::thread t1{snake};
	t1.join();
	

	endwin();
	return 0;
}

Direction getInput(Direction head_nextMove) // takes the heads next move to make sure that the head cannot go in on itself
{
	int input; // ascii value for key pressed
	bool done = false; // true if correct input is give, false if otherwise and need to get input again
	Direction output; // what will be returned 

	while(!done)
	{
		input = getch();

		switch(input)
		{
			case 258: // down arrow key
			done = true;
		       	output = DOWN;
			break;
			
			case 259: // up arrow key
			done = true;
			output = UP;
			break;

			case 260: // right arrow key
			done = true;
			output = RIGHT;
			break;

			case 261: // left arrow key
			done = true;
			output = LEFT;
			break;

			default: // an arrow key was not pressed
			done = false;
			output = MAX_DIRECTIONS;
			break;
		}

		if(head_nextMove == LEFT && output == RIGHT) // opposing directions, snake would go in on itself, get the input again
			done = false;	

		else if(head_nextMove == RIGHT && output == LEFT)
			done = false;
		
		else if(head_nextMove == UP && output == DOWN)
			done = false;

		else if(head_nextMove == DOWN && output == UP)
			done = false;

		
	}

	return output;
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
		--s.x;
		break;

		case LEFT:
		++s.x;
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


void snake() // function to take care of moving the snake
{
	std::vector<Segment> snake = {Segment(0,4,'H',LEFT)}; // element 0 head of the snake
	// snake body segments
	snake.resize(4); // resize once for efficiency
	snake.at(1) = Segment(0,3,'B',LEFT); // body segment 2
	snake.at(2) = Segment(0,2,'B',LEFT); // body segment 3
	snake.at(3) = Segment(0,1,'B',LEFT); // body segment 4

	bool collision = false; // true if snake has collided with itself, false if snake has not collided with itself

	while(!collision) // while the snake has not collided with itself
	{
		snake.at(0).nextMove = getInput(snake.at(0).nextMove); // get the heads direction based on user input, visit getInput() for more info

		moveSegments(snake);
		printSnake(snake);
		collision = findCollision(snake);
	}
}
