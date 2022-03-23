#pragma once

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class QuadIn : public IEasing
	{
	public:
		QuadIn() { };

		static double Calculate(double k)
		{
			return k * k;
		}
	};

	class QuadOut : public IEasing
	{
	public:
		QuadOut() { };

		static double Calculate(double k)
		{
			return 1 - (1 - k) * (1 - k);
		}
	};

	class QuadInOut : public IEasing
	{
	public:
		QuadInOut() { };

		static double Calculate(double k)
		{
			return k < 0.5 ? 2 * k * k : 1 - pow(-2 * k + 2, 2) / 2;
		}
	};
}
