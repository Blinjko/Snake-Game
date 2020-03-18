#ifndef FOOD_H
#define FOOD_H

#include <ncurses.h>

class Food
{
	int m_y;
	int m_x;

	char m_symbol;

	public:

	Food(int y, int x, char symbol); // constructor

	void move(int y, int x); // move the food to the specified x and y coordinates
	void print(WINDOW *win) const; // prints the food to the screen as m_symbol

	void setY(int y); // set the y coordinate
	void setX(int x); // set the x coordinate

	int getY() const; // get the y coordinate
	int getX() const; // get the x coordiante

	void setSymbol(char symbol); // set the symbol

	char getSymbol() const; // get the symbol
};
#endif
