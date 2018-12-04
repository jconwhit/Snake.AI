// Snake.AI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Snake.AI.h"
#include "UI.h"

using namespace std;
int main()
{
	//LoadBG();
	unsigned char board[BOARD_HEIGHT][BOARD_WIDTH];
	vector<unsigned char> v_snake(6, SNAKE);
	vector<int> v_posx(0);
	vector<int> v_posy(0);

	init_snake_pos(v_posx, v_posy);
	init_board(board);
	update_board(board, v_snake, v_posx, v_posy);

	print_board(board);

	cin.get();
    return 0;
}

