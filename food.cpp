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
	mvwprintw(win, m_y, m_x, "%c", m_symbol);
}

// set the y coordinate
void Food::setY(int y)
{
	m_y = y;
}

// set the x coordinate
void Food::setX(int x)
{
	m_x = x;
}

// get the y coordinate
int Food::getY() const
{
	return m_y;
}

// get the x coordinate
int Food::getX() const
{
	return m_x;
}

// set the symbol
void Food::setSymbol(char symbol)
{
	m_symbol = symbol;
}

// get the symbol
char Food::getSymbol() const
{
	return m_symbol;
}
