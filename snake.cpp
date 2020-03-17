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

	Segment(int i_y=0, int i_x=0, char i_symbol='D', Direction i_nextMove=Direction::RIGHT) :
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
	m_segments.resize(size);
	m_segments.at(0) = new Segment(0, size, headSymbol, Direction::RIGHT); // make the head of the snake 

	for(int i{1}; i<size; ++i) // make the body segments
	{
		m_segments.at(i) = new Segment(0, (size-i), bodySymbol, Direction::RIGHT); // creation of body segment
	}
}

// snake deconstructor
Snake::~Snake()
{
	for(Segment *element: m_segments)
	{
		delete element;
	}
}

// prints the snake
void Snake::print(WINDOW *win) const
{
	for(Segment *element: m_segments)
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
			moveSegment(*m_segments.at(i)); // move the head
			m_segments.at(i)->lastMove = m_segments.at(i)->nextMove;
		}
		else
		{
			moveSegment(*m_segments.at(i)); // move a body segment
			m_segments.at(i)->lastMove = m_segments.at(i)->nextMove; // set the last lastMove to the move just made
			m_segments.at(i)->nextMove = m_segments.at(i-1)->lastMove; // set the nextMove to the move just made by the segment before
		}
	}
}

// checks to see if the snake has collided with itself
bool Snake::isDead(int min_y, int max_y, int min_x, int max_x) const
{
	Segment &head = *m_segments.at(0); // get the head

	for(int i{1}; i<m_size; ++i)
	{
		if((m_segments.at(i)->y == head.y) && (m_segments.at(i)->x == head.x))
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



void Snake::addSegment(Segment s) // segment is provided
{
	m_segments.push_back(new Segment(s)); // use copy constructor
	++m_size;
}

void Snake::addSegment() 
{
	Segment *newSegment = new Segment();
	newSegment->symbol = m_segments.at(m_size-1)->symbol; // set body symbol to the same as the other bodies symbols
	newSegment->nextMove = m_segments.at(m_size-1)->lastMove; // the last elements last move becomes the new ones next move
	newSegment->lastMove = newSegment->nextMove; // set lastMove to the same as nextMove

	newSegment->y = m_segments.at(m_size-1)->y; // set the new segments y to the same as the last elements
	newSegment->x = m_segments.at(m_size-1)->x; // set the new segments x to the same as the last elements

	switch(newSegment->nextMove)
	{
		case Direction::UP:
		++newSegment->y;
		break;

		case Direction::DOWN:
		--newSegment->y;
		break;

		case Direction::LEFT:
		++newSegment->x;
		break;

		case Direction::RIGHT:
		--newSegment->x;
		break;
	}

	m_segments.push_back(newSegment);
	++m_size;
}

// pop a segment off the back
void Snake::removeSegment()
{
	m_segments.pop_back(); // pop off last element
	--m_size;
}

// get a certian segment provided an index
Segment*& Snake::at(int index)
{
		return m_segments.at(index); // already does bounds checking
}

// returns the vector of segment pointers
std::vector<Segment*>& Snake::get() 
{
	return m_segments;
}

