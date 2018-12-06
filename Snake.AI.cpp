// Snake.AI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <deque>
#include "Snake.AI.h"
#include "UI.h"
#include "Snake.h"

using namespace std;
int main()
{
	//LoadBG();
	unsigned char board[BOARD_HEIGHT][BOARD_WIDTH];
	deque<Snake> d_snake;
	d_snake.push_back(Snake()); //puts the first piece of the snake at (0,0)
	d_snake.push_back(Snake());
	d_snake.push_back(Snake());
	d_snake.push_back(Snake());


	init_board(board); //initializes an empty playing board
	//update_board(board, d_snake); //puts snake on board
	print_board(board); //prints the playing board and snake

	cin.get();

	while (d_snake.back().getx() < BOARD_WIDTH + 10)
	{
		Sleep(200);

		if (d_snake.back().getx() < 15)
		update_board(board, d_snake, 1); //moves +1 in x dir, 0 in y dir
		else
			update_board(board, d_snake, 0, 1); //moves +1 in x dir, 0 in y dir

		if (!check_end_pos(d_snake))
		{
			break;
		}
	}

	you_died();

	cin.get();
    return 0;
}

