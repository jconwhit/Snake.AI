#ifndef SNAKE_AI_H
#define SNAKE_AI_H

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <deque>
#include "UI.h"
#include "Snake.h"

using namespace std;

const int BOARD_WIDTH = 40;
const int BOARD_HEIGHT = 20;
const int X_MULT = 2;
const int X_OFFSET = 1;
const int Y_OFFSET = 1;
const unsigned char SNAKE = 0xfe; //snake square char
const unsigned char BLANK = ' '; //empty spot
const unsigned char MOUSE = 'O';


void init_board(unsigned char arry[][BOARD_WIDTH]);
void update_board(unsigned char arry[][BOARD_WIDTH], deque<Snake> &deque, int xmod, int ymod);
void remove_tail(deque<Snake> &deque);
void add_head(deque<Snake> &deque);
void set_cursor_pos(int x, int y);

int check_end_pos(deque<Snake> &deque);

void print_board(unsigned char arry[][BOARD_WIDTH]);
void load_top();
void load_bottom();

void you_died(); //end game

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

void update_board(unsigned char arry[][BOARD_WIDTH], deque<Snake> &deque, int xmod = 0, int ymod = 0)
{
	if (deque.size() > 1)
	{
		remove_tail(deque);
		arry[deque.front().gety()][deque.front().getx()] = BLANK; //deletes snake block on board
		deque.pop_front(); //deletes oldest snake block (end of tail)

		deque.push_back(Snake(deque.back().getx() + xmod, deque.back().gety() + ymod)); //inserts new snake object as head
		arry[deque.back().gety()][deque.back().getx()] = SNAKE; //shows snake block on board
		add_head(deque);
	}
	else if (deque.size() == 1)
	{
		remove_tail(deque);
		arry[deque.front().gety()][deque.front().getx()] = BLANK;
		deque.push_back(Snake(deque.back().getx() + xmod, deque.back().gety() + ymod)); //inserts new snake object as head
		arry[deque.back().gety()][deque.back().getx()] = SNAKE;
		deque.pop_front();
		add_head(deque);
	}
	
}

void remove_tail(deque<Snake> &deque)
{
	set_cursor_pos(deque.front().getx(), deque.front().gety());
	std::cout << BLANK;
}

void add_head(deque<Snake> &deque)
{
	set_cursor_pos(deque.back().getx(), deque.back().gety());
	Color(fGREEN);
	std::cout << SNAKE;
	Color(fDEFAULT);
	set_cursor_pos(BOARD_WIDTH + 1, BOARD_HEIGHT);
}

void set_cursor_pos(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { short ((X_MULT*x) + X_OFFSET), short (y + Y_OFFSET) };
	SetConsoleCursorPosition(hOut, coord);
}

int check_end_pos(deque<Snake> &deque)
{
	if ((BOARD_WIDTH > deque.back().getx()) && (BOARD_HEIGHT > deque.back().gety()))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void print_board(unsigned char arry[][BOARD_WIDTH])
{
	load_top();

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		Color(fGREEN);
		std::cout << VERT;
		Color(fDEFAULT);
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (arry[i][j] == SNAKE)
			{
				Color(fGREEN);
				std::cout << arry[i][j] << ' ';
				Color(fDEFAULT);
			}
			else
			{
				std::cout << arry[i][j] << ' ';
			}
		}
		Color(fGREEN);
		std::cout << VERT;
		Color(fDEFAULT);
		std::cout << endl;
	}
	load_bottom();
}

void load_top()
{
	Color(fGREEN);

	std::cout << UL;

	for (int i = 0; i < (X_MULT*BOARD_WIDTH); i++)
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

	for (int i = 0; i < (X_MULT*BOARD_WIDTH); i++)
	{
		std::cout << HORIZ;
	}

	std::cout << LR << endl;

	Color(fDEFAULT);
}

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
