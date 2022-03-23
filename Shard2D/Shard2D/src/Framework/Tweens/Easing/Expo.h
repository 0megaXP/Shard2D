#pragma once

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class ExpoIn : public IEasing
	{
	public:
		ExpoIn() { };

		static double Calculate(double k)
		{
			if (k == 0)
				return 0;
			else
				return pow(2, 10 * k - 10);
		}
	};

	class ExpoOut : public IEasing
	{
	public:
		ExpoOut() { };

		static double Calculate(double k)
		{
			if (k == 1)
				return 1;
			else
				return 1 - pow(2, -10 * k);
		}
	};

	class ExpoInOut : public IEasing
	{
	public:
		ExpoInOut() { };

		static double Calculate(double k)
		{
			if (k == 0)
				return 0;
			else if (k == 1)
				return 1;
			else if (k < 0.5)
				return pow(2, 20 * k - 10) / 2;
			else
				return (2 - pow(2, -20 * k + 10)) / 2;
		}
	};
}
