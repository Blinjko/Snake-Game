#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector> // for forward declarations
#include <mutex> // for forward declarations

enum Direction // directions that Segments of the snake can move in
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX_DIRECTIONS,
};

struct Segment;


void threadOneJob(); // fucntion that moves the snake
void threadTwoJob(std::vector<Segment> &s, std::mutex &m); // thread two job, will listen for input while thread 1 moves the snake
Direction getInput(); // gets input and depending on arrow key pressed it returns the corresponding Direction type
void printSnake(std::vector<Segment> &snake); // prints the snake to the screen
void moveSegments(std::vector<Segment> &snake); // after input is gotten and the heads direction is changed, call this to move the body segments appropriately
void moveSegment(Segment &s); // moves a singular segment based upon its next movement
bool findCollision(std::vector<Segment> &snake); // looks to see if the snakes head has hit one of the body segments, if so return true, else return false
int generateRandom(int min, int max); // generates a random between the range of min and max

#endif
