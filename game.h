#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <vector>
#include <mutex>
#include <random>
#include "food.h"
#include "snake.h"

class Game
{
	Snake m_snake;
	Food m_food;
	
	// the windows max x and and max y
	int m_max_y;
	int m_max_x;

	// the windows min x and min y
	int m_min_y;
	int m_min_x;

	// the operating window
	WINDOW *m_window;

	// mutex
	std::mutex m_gameMutex;

	// points the player has
	int m_points;

	// is the game over, true == yes, false == no
	bool m_over;

	//mersenne twister engine
	std::mt19937 m_mt;

	public:

	Game(Snake s, Food f, WINDOW *window, int min_y, int max_y, int min_x, int max_x);

	bool play(); // returns true if the player won, false if otherwise

	private:

	void getInput(); // gets input and sets the heads direction based on input given
	
	void spawnFood(); // spawn the food, set its location to a randomly generated one

	bool foodEaten(); // checks to see if the food was eaten by the snake

	int generateRandom(int min, int max); // generates a random number between the min and max values

};

#endif
