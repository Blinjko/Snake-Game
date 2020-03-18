#include <ncurses.h>
#include <vector>
#include <mutex>
#include <thread>
#include <random>
#include <ctime>
#include "game.h"
#include "food.h"
#include "snake.h"


// constructor
Game::Game(Snake s, Food f, WINDOW *window, int min_y, int max_y, int min_x, int max_x) :
       m_snake{s}, m_food{f}, m_window{window}, m_max_y{max_y}, m_max_x{max_x}, m_min_y{min_y}, m_min_x{min_x},
       m_points{0}, m_over{false}, m_mt{static_cast<std::size_t>(std::time(nullptr))}; // seed the rng with system time 
{
}	

// gets direction input from arrow keys and sets the heads nextMove
void Game::getInput() 
{
	Direction newMove;
	int input;

	while(true)
	{
		input = getch();

		switch(input)
		{
			case 258: // Down arrow key
			newMove = Direction::DOWN;
			break;

			case 259: // up arrow key
			newMove = Direction::UP;
			break;

			case 260: // left arrow key
			newMove = Direction::LEFT;
			break;

			case 261:
			newMove = Direction::RIGHT;
			break;

			default:
			newMove = Direction::MAX_DIRECTIONS;
			break;
		}

		std::lock_guard<std::mutex> lock{m_gameMutex}; // get mutex to avoid race conditions

		// check to see if the snake is dead, if so break the loop
		if(m_snake.isDead(m_min_y, m_max_y, m_min_x, m_max_x))
			break;

		// the follow are conditions where the snake could turn in on itself or invalid input was given
		else if((newMove == Direction::UP) && (m_snake.at(0)->lastMove == Direction::DOWN))
			continue;

		else if((newMove == Direction::DOWN) && (m_snake.at(0)->lastMove == Direction::UP))
			continue;

		else if((newMove == Direction::LEFT) && (m_snake.at(0)->lastMove == Direction::RIGHT))
			continue;

		else if((newMove == Direction::RIGHT) && (m_snake.at(0)->lastMove == Direction::LEFT))
			continue;
		
		else if(newMove == Direction::MAX_DIRECTIONS) // invalid input was given
			continue;

		else
		{
			m_snake.at(0)->nextMove = newMove;
		}
	}

}

// generates a random number between the specified values
int Game::generateRandom(int min, int max)
{
	std::uniform_int_distribution<int> random{min,max};
	return random{m_mt}; // return a random number
}
