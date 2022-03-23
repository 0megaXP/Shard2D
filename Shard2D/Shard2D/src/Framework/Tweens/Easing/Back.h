#pragma once

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class BackIn : public IEasing
	{
	public:
		BackIn() { };

		static double Calculate(double k)
		{
			return 2.70158 * k * k * k - 1.70158 * k * k;
		}
	};

	class BackOut : public IEasing
	{
	public:
		BackOut() { };

		static double Calculate(double k)
		{
			return 1 + 2.70158 * pow(k - 1, 3) + 1.70158 * pow(k - 1, 2);
		}
	};

	class BackInOut : public IEasing
	{
	public:
		BackInOut() { };

		static double Calculate(double k)
		{
			if (k < 0.5)
				return  (pow(2 * k, 2) * ((1.70158 * 1.525 + 1) * 2 * k - 1.70158 * 1.525)) / 2;
			else
				return (pow(2 * k - 2, 2) * ((1.70158 * 1.525 + 1) * (k * 2 - 2) + 1.70158 * 1.525) + 2) / 2;
		}
	};
}
