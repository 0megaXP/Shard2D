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

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class ElasticIn : public IEasing
	{
	public:
		ElasticIn() { };

		static double Calculate(double k)
		{
			if (k == 0)
				return 0;
			else
				if (k == 1)
					return 1;
				else
					return -pow(2, 10 * k - 10) * sin((k * 10 - 10.75) * ((2 * M_PI) / 3));
		}
	};

	class ElasticOut : public IEasing
	{
	public:
		ElasticOut() { };

		static double Calculate(double k)
		{
			if (k == 0)
				return 0;
			else
				if (k == 1)
					return 1;
				else
					return pow(2, -10 * k) * sin((k * 10 - 0.75) * ((2 * M_PI) / 3)) + 1;
		}
	};

	class ElasticInOut : public IEasing
	{
	public:
		ElasticInOut() { };

		static double Calculate(double k)
		{
			if (k == 0)
				return 0;
			else
				if (k == 1)
					return 1;
				else if(k < 0.5)
					return -(pow(2, 20 * k - 10) * sin((20 * k - 11.125) * ((2 * M_PI) / 4.5))) / 2;
				else
					return (pow(2, -20 * k + 10) * sin((20 * k - 11.125) * ((2 * M_PI) / 4.5))) / 2 + 1;
		}
	};
}