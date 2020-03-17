#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <ncurses.h>

struct Segment;

class Snake
{
	std::vector<Segment*> m_segments;
	int m_size;
	
	public:

		Snake(char headSymbol='H', char bodySymbol='B', int size=4);
	
		~Snake();

		void print(WINDOW *win) const;

		void move();

		bool isDead(int min_y, int max_y, int min_x, int max_x) const;

		void addSegment(Segment s); // segment is provided
		void addSegment(); // nothing is provided and the segment will be made accordingly
		void removeSegment(); // pop a segment off the back

		Segment*& at(int index); // get a particular segment at an index

		std::vector<Segment*>& get(); // returns the Segment vector
	
		int size() const { return m_size; }

};
#endif
