#include <ncurses.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <random>
#include "snake.h"
#include "food.h"
#include "game.h"

int main()
{
    bool playing = true;

    while(playing)
    {
        initscr(); // initialize the screen for ncurses
        noecho(); // make sure any characters typed dont get displayed on screen
        keypad(stdscr, true); // enable the keypad, allows for input from arrow keys and other keys

        // set minimum x and y coordinates
        int min_y = 0;
        int min_x = 0;

        // get the maximun x and y coordinates
        int max_y;
        int max_x;
        getmaxyx(stdscr, max_y, max_x);

        // make the snake
        Snake snake{'H','B',4}; 

        // make the food
        Food food{10,10,'F'};


        // make the game
        // subtract 1 from max x and y because ncurses is odd and 
        Game game{snake, food, stdscr, min_y, max_y-1, min_x, max_x-1};


        // play the game
        int score = game.play();

        endwin(); // stop ncurses

        // print the score
        std::cout << "Your score was: " << score << std::endl;

        // ask the user to play again
        // makes sure the user does valid input
        while(true)
        {
            std::cout << "Would you like to play again(y/n): ";
            char input;
            std::cin >> input;

            if(std::cin.fail())
            {
                std::cout << "Invalid input" << std::endl;
                std::cin.clear(); // rest std::cin
                std::cin.ignore(32767,'\n'); // clear the input buffer
            }

            else if(input == 'y')
            {
                playing = true; // player is playing again
                break;
            }
            else if(input == 'n')
            {
                playing = false; // not playing again
                break;
            }
            else
            {
                std::cout << "Invalid input" << std::endl;
                std::cin.ignore(32767, '\n');
            }
        }
        
    }
    return 0;
}
