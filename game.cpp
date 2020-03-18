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
       m_points{0}, m_over{false}, m_mt{static_cast<std::size_t>(std::time(nullptr))} // seed the rng with system time 
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
		{
			m_over = true;
			break;
		}

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
			break;
		}
	}

}

// generates a random number between the specified values
int Game::generateRandom(int min, int max)
{
	std::uniform_int_distribution<int> random{min,max};
	return random(m_mt); // return a random number
}

// moves the food to a random location
void Game::spawnFood()
{
	// we add 1 to minimum because the border takes up 1 tile and we dont want food to spawn in the border
	// we subtract 1 from the max for the same reason
	
	int newY{generateRandom(m_min_y+1, m_max_y-1)}; // generate new y coordinate
	int newX{generateRandom(m_min_x+1, m_max_x-1)};

	// check to see if the food spawned inside the snake
	for(int i{0}; i<m_snake.size(); ++i)
	{
		// food spawned inside the snake
		if((m_snake.at(i)->y == newY) && (m_snake.at(i)->x == newX)) 
		{
			// generate new coordinates
			newY = generateRandom(m_min_y+1, m_max_y-1);
			newX = generateRandom(m_min_x+1, m_max_x-1);
			
			// set i to 0 to once again make sure the food did not spawn in the snake
			i = 0;
		}
	}
	// move the food to the new location
	m_food.move(newY, newX);
}

// checks to see if the food has been eaten
bool Game::foodEaten()
{
	// return true if the snakes head is in the same spot as the food
	return ((m_snake.at(0)->y == m_food.getY()) && (m_snake.at(0)->x == m_food.getX()));
}

// the function that starts the snake game, returns the score
int Game::play()
{
	// start another thread to get input
	//std::thread t2{getInput};

	// clear anything that was on the screen
	wclear(m_window);
	
	// initial setup
	spawnFood();
	m_food.print(m_window);
	m_snake.print(m_window);
	wrefresh(m_window);

	while(true)
	{
		getInput();

		m_snake.move();
		
		// snake hit itself and and game is over
		if(m_snake.isDead(m_min_y, m_max_y, m_min_x, m_max_x))
		{
			m_over = true;
			clear();
			mvprintw(0,0, "Snake ded");
			refresh();
			break;
		}

		// has food been eaten
		else if(foodEaten())
		{
			// add segment to the snake
			m_snake.addSegment();

			// spawn a new piece of food
			spawnFood();

			// increment the points
			++m_points;
		}

		// print the snake and food
		wclear(m_window);
		m_snake.print(m_window);
		m_food.print(m_window);
		wborder(m_window, '|','|', '-', '-', '+', '+', '+', '+');
		wrefresh(m_window);
		
		// move cursor into corner for prettiness
		wmove(m_window, 0,0);
	}
	return m_points;
}

