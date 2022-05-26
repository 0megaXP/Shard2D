/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <iostream>
#include <windows.h>

namespace Shard2D
{
	class TextColor
	{
	public:
		static inline const int Blue = 1;
		static inline const int Green = 2;
		static inline const int Aqua = 3;
		static inline const int Red = 12;
		static inline const int Purple = 5;
		static inline const int Yellow = 6;
		static inline const int White = 7;
		static inline const int Gray = 8;
	};

	static void inline Log(const auto text, int textColor = 7)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		//std::cout << std::endl;
		SetConsoleTextAttribute(hConsole, textColor);
		std::cout << text << std::endl;
		SetConsoleTextAttribute(hConsole, TextColor::White);
	}

	static void DebugFPS(float FPS, int textColor = 7)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		std::cout << "\r";
		for (int a = 0; a < 20; a++)
			std::cout << " ";

		std::cout << "\r";
		SetConsoleTextAttribute(hConsole, textColor);
		std::cout << "FPS: " << FPS;
		SetConsoleTextAttribute(hConsole, TextColor::White);
	}
}