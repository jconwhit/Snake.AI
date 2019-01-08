#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <iomanip>
#include <deque>
#include "Snake.AI.h"
#include <time.h>

class Mouse
{
public:
	//constructor
	Mouse()
	{
		srand(time(NULL));
		x_pos = rand() % BOARD_WIDTH;
		y_pos = rand() % BOARD_HEIGHT;
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