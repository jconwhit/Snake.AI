#ifndef SNAKE_AI_H
#define SNAKE_AI_H

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include "UI.h"

using namespace std;

const int BOARD_WIDTH = 40;
const int BOARD_HEIGHT = 20;
const unsigned char SNAKE = 0xfe; //snake square


void init_board(unsigned char arry[][BOARD_WIDTH]);
void init_snake_pos(vector<int> &vx, vector<int> &vy);
void update_board(unsigned char arry[][BOARD_WIDTH], vector<unsigned char> v_snake, 
	vector<int> vx, vector<int> vy);
void print_board(unsigned char arry[][BOARD_WIDTH]);

void init_board(unsigned char arry[][BOARD_WIDTH])
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			arry[i][j] = ' ';
		}
	}
}

void init_snake_pos(vector<int> &vx, vector<int> &vy)
{
	vx.clear();
	vx.push_back(0);
	vx.push_back(1);
	vx.push_back(2);
	vx.push_back(3);
	vx.push_back(4);
	vx.push_back(4);

	vy.clear();
	vy.push_back(3);
	vy.push_back(3);
	vy.push_back(3);
	vy.push_back(3);
	vy.push_back(3);
	vy.push_back(4);
}

void update_board(unsigned char arry[][BOARD_WIDTH], vector<unsigned char> v_snake, 
	vector<int> vx, vector<int> vy)
{
	for (int i = 0; i < v_snake.size(); i++)
	{
		arry[vy[i]][vx[i]] = SNAKE;
	}
}

void print_board(unsigned char arry[][BOARD_WIDTH])
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (arry[i][j] == SNAKE)
			{
				Color(fGREEN);
				cout << arry[i][j] << ' ';
				Color(fDEFAULT);
			}
			else
			{
				cout << arry[i][j] << ' ';
			}
		}
		cout << endl;
	}
}

#endif // !SNAKE_AI_H
