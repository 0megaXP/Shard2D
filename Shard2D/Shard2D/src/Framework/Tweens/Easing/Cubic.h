#pragma once

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class CubicIn : public IEasing
	{
	public:
		CubicIn() { };

		static double Calculate(double k)
		{
			return k * k * k;
		}
	};

	class CubicOut : public IEasing
	{
	public:
		CubicOut() { };

		static double Calculate(double k)
		{
			return 1 - pow(1 - k, 3);
		}
	};

	class CubicInOut : public IEasing
	{
	public:
		CubicInOut() { };

		static double Calculate(double k)
		{
			return k < 0.5 ? 4 * k * k * k : 1 - pow(-2 * k + 2, 3) / 2;
		}
	};
}
