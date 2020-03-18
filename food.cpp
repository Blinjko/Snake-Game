#include "food.h"
#include <ncurses.h>

// constructor
Food::Food(int y, int x, char symbol) :
	m_y{y}, m_x{x}, m_symbol{symbol}
{
}

// move the food to the specified y and x coordinate
void Food::move(int y, int x)
{
	m_y = y;
	m_x = x;
}

// print the food as m_symbol to the specified window
void Food::print(WINDOW *win) const
{
	mvwprintw(win, m_y, m_x, "%c", symbol);
}

// set the y coordinate
void setY(int y)
{
	m_y = y;
}

// set the x coordinate
void setX(int x)
{
	m_x = x;
}

// get the y coordinate
int getY() const
{
	return m_y;
}

// get the x coordinate
int getX() const
{
	return m_x;
}

// set the symbol
void setSymbol(char symbol)
{
	m_symbol = symbol;
}

// get the symbol
char getSymbol() const
{
	return m_symbol;
}
