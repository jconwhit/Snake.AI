// Snake.AI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <deque>
#include "Snake.AI.h"
#include "UI.h"
#include "Snake.h"
#include "Mouse.h"

using namespace std;
int main()
{
	//LoadBG();
	bool play = true;
	short x = 1;
	short y = 0;
	unsigned char board[BOARD_HEIGHT][BOARD_WIDTH];
	deque<Snake> d_snake;
	d_snake.push_back(Snake(1, BOARD_HEIGHT / 2)); //puts the first piece of the snake at (0,0)
	d_snake.push_back(Snake(2, BOARD_HEIGHT / 2));
	d_snake.push_back(Snake(3, BOARD_HEIGHT / 2));
	d_snake.push_back(Snake(4, BOARD_HEIGHT / 2));
	d_snake.push_back(Snake(5, BOARD_HEIGHT / 2));

	init_board(board); //initializes an empty playing board
	init_deque(board, d_snake); //initializes position of snake in array
	print_board(board, d_snake); //prints the playing board and snake

	Mouse Tom;
	set_cursor_pos(Tom.getx(), Tom.gety());
	Color(fRED);
	std::cout << MOUSE;
	Color(fDEFAULT);

	/*
	while ((getchar()) != '\n')
		;*/

	//use WASD for movement
	while (play)
	{
		Sleep(200);

		keypress(x, y);
		play = update_board(board, d_snake, x, y);
	}

	you_died();

	cin.get();
    return 0;
}

