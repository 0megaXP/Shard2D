#pragma once

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class CircIn : public IEasing
	{
	public:
		CircIn() { };

		static double Calculate(double k)
		{
			return 1 - sqrt(1 - pow(k, 2));
		}
	};

	class CircOut : public IEasing
	{
	public:
		CircOut() { };

		static double Calculate(double k)
		{
			return sqrt(1 - pow(k - 1, 2));
		}
	};

	class CircInOut : public IEasing
	{
	public:
		CircInOut() { };

		static double Calculate(double k)
		{
			if (k < 0.5)
				return (1 - sqrt(1 - pow(2 * k, 2))) / 2;
			else
				return (sqrt(1 - pow(-2 * k + 2, 2)) + 1) / 2;
		}
	};
}
