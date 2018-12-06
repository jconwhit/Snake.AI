#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <iomanip>
#include <deque>

class Snake
{
public:
	Snake(int x_init = 0, int y_init = 0) : x_pos(x_init), y_pos(y_init) //constructor
	{
		
	}

	int getx() { return x_pos; };
	int gety() { return y_pos; };

	void setx(int x) { x_pos = x; };
	void sety(int y) { y_pos = y; };

private:
	int x_pos;
	int y_pos;
};


#endif
