#pragma once

#include <iostream>
#include <windows.h>

class TextColor
{
public:
	static inline const int Blue =		1;
	static inline const int Green =		2;
	static inline const int Aqua =		3;
	static inline const int Red =		12;
	static inline const int Purple =	5;
	static inline const int Yellow =	6;
	static inline const int White =		7;
	static inline const int Gray =		8;
};

static void inline Log(const char text[], int textColor = 7)
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "\r";
	SetConsoleTextAttribute(hConsole, textColor);
	std::cout << text << std::endl;
	SetConsoleTextAttribute(hConsole, TextColor::White);
}

static void DebugFPS(float FPS, int textColor = 7)
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "\r";
	for (int a = 0; a < 20; a++)
		std::cout << " ";

	std::cout << "\r";
	SetConsoleTextAttribute(hConsole, textColor);
	std::cout << "FPS: " << FPS;
	SetConsoleTextAttribute(hConsole, TextColor::White);
}