#pragma once

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class QuartIn : public IEasing
	{
	public:
		QuartIn() { };

		static double Calculate(double k)
		{
			return k * k * k * k;
		}
	};

	class QuartOut : public IEasing
	{
	public:
		QuartOut() { };

		static double Calculate(double k)
		{
			return 1 - pow(1 - k, 4);
		}
	};

	class QuartInOut : public IEasing
	{
	public:
		QuartInOut() { };

		static double Calculate(double k)
		{
			return k < 0.5 ? 8 * k * k * k * k : 1 - pow(-2 * k + 2, 4) / 2;
		}
	};
}
