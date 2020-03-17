#include "snake.h"
#include <ncurses.h>
#include <vector>

enum class Direction
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	MAX_DIRECTIONS,
};


struct Segment
{
	int y; // y coordinate
	int x; // x coordinate
	Direction lastMove; // last moving direction
	Direction nextMove; // next moving direction

	char symbol; // charater the segment will be printed as

	Segment(int i_y, int i_x, char i_symbol, Direction i_nextMove=Direction::RIGHT) :
		y{i_y}, x{i_x}, symbol{i_symbol}, nextMove{i_nextMove}, lastMove{i_nextMove}
	{
	}
};

// moves a segment based upon its movements
void moveSegment(Segment &s)
{
	switch(s.nextMove)
	{
		case Direction::UP:
		--s.y;
		break;

		case Direction::DOWN:
		++s.y;
		break;

		case Direction::LEFT:
		--s.x;
		break;

		case Direction::RIGHT:
		++s.x;
		break;
	}
}


// snake constructor
Snake::Snake(char headSymbol, char bodySymbol, int size)
	: m_size{size}
{
	segments.resize(size);
	segments.at(0) = new Segment(0, size, headSymbol, Direction::RIGHT); // make the head of the snake 

	for(int i{1}; i<size; ++i) // make the body segments
	{
		segments.at(i) = new Segment(0, (size-i), bodySymbol, Direction::RIGHT); // creation of body segment
	}
}

// snake deconstructor
Snake::~Snake()
{
	for(Segment *element: segments)
	{
		delete element;
	}
}

// prints the snake
void Snake::print(WINDOW *win) const
{
	for(Segment *element: segments)
	{
		mvwprintw(win, element->y, element->x, "%c", element->symbol);
	}
}


// moves the snake
void Snake::move()
{
	for(int i{0}; i<m_size; ++i)
	{
		if(i == 0)
		{
			moveSegment(*segments.at(i)); // move the head
			segments.at(i)->lastMove = segments.at(i)->nextMove;
		}
		else
		{
			moveSegment(*segments.at(i)); // move a body segment
			segments.at(i)->lastMove = segments.at(i)->nextMove; // set the last lastMove to the move just made
			segments.at(i)->nextMove = segments.at(i-1)->lastMove; // set the nextMove to the move just made by the segment before
		}
	}
}

// checks to see if the snake has collided with itself
bool Snake::isDead(int min_y, int max_y, int min_x, int max_y) const
{
	Segment &head = *segments.at(0); // get the head

	for(int i{1}; i<m_size; ++i)
	{
		if((segments.at(i)->y == head.y) && (segments.at(i)->x == head.x))
		{
			return true; // collision found
		}
	}

	if((head.x == min_x) || (head.x == max_x))
		return true; // head hit left or right border 

	else if((head.y == min_y) || (head.y == max_y))
		return true; // head hit top of bottom border

	return false; // no collision found
}



void addSegment(Segment s); // segment is provided
void addSegment(); // nothing is provided and the segment will be made accordingly
void removeSegment(); // pop a segment off the back

Segment*& at(int index); // get a particular segment at an index

std::vector<Segment*>& get(); // returns the Segment vector

int size() const { return m_size; }
