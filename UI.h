#ifndef UI_H
#define UI_H

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <vector>

const int fDEFAULT = 7;
const int fGREEN = 10;
const int bWHITE = 240;
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);



void LoadBG();
void Color(int color_selection);



// char definitions
const unsigned char UL = 0xda;		// upper left
const unsigned char UR = 0xbf;		// upper right
const unsigned char LL = 0xc0;		// lower left
const unsigned char LR = 0xd9;		// lower right
const unsigned char HORIZ = 0xc4;	// horizontal bar
const unsigned char CR = 0xc3;		// cross to the right
const unsigned char CL = 0xb4;		// cross to the left
const unsigned char CU = 0xc1;		// cross up 
const unsigned char CD = 0xc2;		// cross down
const unsigned char VERT = 0xb3;	// vertical bar
const unsigned char CROSS = 0xc5;	// crosses




const short MAX_LINE_LENGTH = 79;	// longest line allowed
const int OFFSET = 2;			// number of start & end chars



void LoadBG()
{
	Color(fGREEN);
	std::cout << UL;
	for (int i = 0; i < (MAX_LINE_LENGTH-OFFSET); i++)
		std::cout << HORIZ;
	std::cout << UR << std::endl;

	for (int j = 0; j < 15; j++)
	{
		if (j == 7)
		{
			std::cout << VERT;
			for (int i = 0; i < (28); i++)
				std::cout << ' ';
			std::cout << "WELCOME TO SNAKE.AI!";
				for (int i = 0; i < (29); i++)
					std::cout << ' ';
			std::cout << VERT << std::endl;
		}
		else 
		{
			std::cout << VERT;
			for (int i = 0; i < (MAX_LINE_LENGTH - OFFSET); i++)
				std::cout << ' ';
			std::cout << VERT << std::endl;
		}
	}


	std::cout << LL;
	for (int i = 0; i < (MAX_LINE_LENGTH - OFFSET); i++)
		std::cout << HORIZ;
	std::cout << LR << std::endl;

	Color(fDEFAULT);
}

void Color(int color_selection)
{
	SetConsoleTextAttribute(hCon, color_selection);
}


#endif // !UI_H
