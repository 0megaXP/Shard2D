#pragma once

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class QuintIn : public IEasing
	{
	public:
		QuintIn() { };

		static double Calculate(double k)
		{
			return k * k * k * k * k;
		}
	};

	class QuintOut : public IEasing
	{
	public:
		QuintOut() { };

		static double Calculate(double k)
		{
			return 1 - pow(1 - k, 5);
		}
	};

	class QuintInOut : public IEasing
	{
	public:
		QuintInOut() { };

		static double Calculate(double k)
		{
			return k < 0.5 ? 16 * k * k * k * k * k : 1 - pow(-2 * k + 2, 5) / 2;
		}
	};
}
