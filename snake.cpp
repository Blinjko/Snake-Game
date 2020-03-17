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


