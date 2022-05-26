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
	class BounceOut : public IEasing
	{
	public:
		BounceOut() { };

		static double Calculate(double k)
		{
			if (k < 1 / 2.75)
				return 7.5625 * k * k;
			else if (k < 2 / 2.75)
				return 7.5625 * (k -= 1.5 / 2.75) * k + 0.75;
			else if (k < 2.5 / 2.75)
				return 7.5625 * (k -= 2.25 / 2.75) * k + 0.9375;
			else
				return 7.5625 * (k -= 2.625 / 2.75) * k + 0.984375;
		}
	};

	class BounceIn : public IEasing
	{
	public:
		BounceIn() { };

		static double Calculate(double k)
		{
			return 1 - BounceOut::Calculate(1 - k);
		}
	};

	class BounceInOut : public IEasing
	{
	public:
		BounceInOut() { };

		static double Calculate(double k)
		{
			if (k < 0.5)
				return (1 - BounceOut::Calculate(1 - 2 * k)) / 2;
			else
				return (1 + BounceOut::Calculate(2 * k - 1)) / 2;
		}
	};
}
