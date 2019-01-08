#ifndef SNAKE_AI_H
#define SNAKE_AI_H

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <deque>
#include "UI.h"
#include "Snake.h"
#include <conio.h>

using namespace std;

//board dimensions
const int BOARD_WIDTH = 40; //its just the board width
const int BOARD_HEIGHT = 20; //this one is the HEIGHT tho

//matches visuals of x and y output increments [y = 2x by default]
//no functionality support for values other than 2
const int X_MULT = 2;

//moves initial "x" position to match board origin
const int X_OFFSET = 2;

//moves initial "y" position to match board origin
const int Y_OFFSET = 1;

//special chars for visual output
const unsigned char SNAKE = 0xfe; //snake square char
const unsigned char BLANK = ' '; //empty spot
const unsigned char MOUSE = '#'; //mouse char

//forward declarations
void init_board(unsigned char arry[][BOARD_WIDTH]);
void init_deque(unsigned char arry[][BOARD_WIDTH], deque<Snake> deque);
bool update_board(unsigned char arry[][BOARD_WIDTH], deque<Snake> &deque, int xmod, int ymod);
void remove_tail(deque<Snake> deque);
void head_recolor(deque<Snake> deque);
void add_head(deque<Snake> deque);
bool check_body_collision(deque<Snake> &deque, int xmod, int ymod);
void dead_head(deque<Snake> deque, int xmod, int ymod);
void set_cursor_pos(int x, int y);
bool check_end_cond(deque<Snake> &deque);
void print_board(unsigned char arry[][BOARD_WIDTH], deque<Snake> &deque);
void load_top();
void load_bottom();
void keypress(short &x, short &y);
void you_died(); //end game

//initializes an empty arry[BOARD_HEIGHT][BOARD_WIDTH]
void init_board(unsigned char arry[][BOARD_WIDTH])
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			arry[i][j] = BLANK;
		}
	}
}

//loads all deque elements into array
void init_deque(unsigned char arry[][BOARD_WIDTH], deque<Snake> deque)
{
	for (int i = 0; i < deque.size(); i++)
	{
		arry[deque[i].gety()][deque[i].getx()] = SNAKE;
	}
}

//moves the snake by deleting the end of the tail and creating a new object as the head
bool update_board(unsigned char arry[][BOARD_WIDTH], deque<Snake> &deque, int xmod = 0, int ymod = 0)
{
	if ((((deque.back().getx()) + xmod) >= 0) && (((deque.back().getx()) + xmod) < BOARD_WIDTH) &&
		(((deque.back().gety()) + ymod) >= 0) && (((deque.back().gety()) + ymod) < BOARD_HEIGHT) &&
		check_body_collision(deque, xmod, ymod))
	{
		remove_tail(deque);
		head_recolor(deque);

		//deletes snake block on board
		arry[deque.front().gety()][deque.front().getx()] = BLANK;

		//inserts new snake object as head
		deque.push_back(Snake(deque.back().getx() + xmod, deque.back().gety() + ymod));

		//draws snake block on board
		arry[deque.back().gety()][deque.back().getx()] = SNAKE;

		add_head(deque);

		//deletes oldest snake block (end of tail) 
		//[needs to be at the end in case the deque size is only 1]
		deque.pop_front();
		return true;
	}
	else
	{
		remove_tail(deque);
		head_recolor(deque);
		dead_head(deque, xmod, ymod);
		return false;
	}
}

//erases last snake block/tail from the board (visually only)
void remove_tail(deque<Snake> deque)
{
	set_cursor_pos(deque.front().getx(), deque.front().gety());
	std::cout << BLANK;
}

//returns the color of the head to fDEFAULT
void head_recolor(deque<Snake> deque)
{
	set_cursor_pos(deque.back().getx(), deque.back().gety());
	std::cout << SNAKE;
	set_cursor_pos(-1, BOARD_HEIGHT + 2);
}

//draws snake head on the board (visually only)
void add_head(deque<Snake> deque)
{
	set_cursor_pos(deque.back().getx(), deque.back().gety());
	Color(fGREEN);
	std::cout << SNAKE;
	Color(fDEFAULT);
	set_cursor_pos(-1, BOARD_HEIGHT + 2);
}

//checks if the next move will collide with the body of the snake,
//not including the tail
bool check_body_collision(deque<Snake> &deque, int xmod, int ymod)
{
	//starts with the second piece from the tail, 
	//not including the last piece for collision purposes
	for (int i = 1; i < deque.size(); i++) 
	{
		if (((deque.back().getx() + xmod) == deque[i].getx()) &&
			((deque.back().gety() + ymod) == deque[i].gety()))
		{
			return false;
		}
	}

	return true;
}

void dead_head(deque<Snake> deque, int xmod, int ymod)
{
	set_cursor_pos(deque.back().getx() + xmod, deque.back().gety() + ymod);
	Color(fRED);
	std::cout << SNAKE;
	Color(fDEFAULT);
	set_cursor_pos(-1, BOARD_HEIGHT + 2);
}

//sets the cursor to a location in the console relative to the origin of the board array
//for printing visuals
void set_cursor_pos(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { short ((X_MULT*x) + X_OFFSET), short (y + Y_OFFSET) };
	SetConsoleCursorPosition(hOut, coord);
}

bool check_end_cond(deque<Snake> &deque)
{
	if ((BOARD_WIDTH > deque.back().getx()) && (BOARD_HEIGHT > deque.back().gety()) && 
		(deque.back().getx() >= 0) && (deque.back().gety() >= 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void print_board(unsigned char arry[][BOARD_WIDTH], deque<Snake> &deque)
{
	load_top();

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		Color(fGREEN);
		std::cout << VERT << ' ';
		Color(fDEFAULT);
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			std::cout << arry[i][j] << ' ';
		}
		Color(fGREEN);
		std::cout << VERT;
		Color(fDEFAULT);
		std::cout << endl;
	}
	load_bottom();
	add_head(deque);
}

void load_top()
{
	Color(fGREEN);

	std::cout << UL;

	for (int i = 0; i < ((X_MULT*BOARD_WIDTH) + 1); i++)
	{
		std::cout << HORIZ;
	}

	std::cout << UR << endl;

	Color(fDEFAULT);
}

void load_bottom()
{
	Color(fGREEN);

	std::cout << LL;

	for (int i = 0; i < ((X_MULT*BOARD_WIDTH) + 1); i++)
	{
		std::cout << HORIZ;
	}

	std::cout << LR << endl;

	Color(fDEFAULT);
}

void keypress(short &x, short &y)
{
	unsigned char c;
	cin.clear();
	if (_kbhit())
	{
		switch (c = _getch())
		{
		case 'w':
			if (y != 1)
			{
				x = 0;
				y = -1;
			}
			break;
		case 'a':
			if (x != 1)
			{
				x = -1;
				y = 0;
			}
			break;
		case 'd':
			if (x != -1)
			{
				x = 1;
				y = 0;
			}
			break;
		case 's':
			if (y != -1)
			{
				x = 0;
				y = 1;
			}
			break;
		}
		
		cin.sync();
	}

}

//prints DS "YOU DIED" on screen
void you_died()
{
	Color(fRED);

	set_cursor_pos((BOARD_WIDTH / 2) - 3, (BOARD_HEIGHT / 2) - 2);
	std::cout << UL;
	for (short i = 0; i < 11; i++)
		std::cout << HORIZ;
	std::cout << UR;

	set_cursor_pos((BOARD_WIDTH / 2) - 3, (BOARD_HEIGHT / 2) - 1);
	std::cout << VERT << " YOU  DIED " << VERT;

	set_cursor_pos((BOARD_WIDTH / 2) - 3, (BOARD_HEIGHT / 2));
	std::cout << LL;
	for (short i = 0; i < 11; i++)
		std::cout << HORIZ;
	std::cout << LR;

	Color(fDEFAULT);

	set_cursor_pos(BOARD_WIDTH + 1, BOARD_HEIGHT);
}

#endif // !SNAKE_AI_H
