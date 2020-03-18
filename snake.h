#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <ncurses.h>

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

void moveSegment(Segment&);

class Snake
{
	std::vector<Segment*> m_segments;
	int m_size;

	public:

	Snake(char headSymbol, char bodySymbol, int size);

	~Snake();

	void print(WINDOW *win) const;

	void move();

	bool isDead(int min_y, int max_y, int min_x, int max_x) const;

	void addSegment(Segment s); // segment is provided
	void addSegment(); // nothing is provided and the segment will be made accordingly
	void removeSegment(); // pop a segment off the back

	Segment*& at(int index); // get a particular segment at an index

	std::vector<Segment*>& get(); // returns the Segment vector

	int size() const; // gets the size of the snake

};
#endif
