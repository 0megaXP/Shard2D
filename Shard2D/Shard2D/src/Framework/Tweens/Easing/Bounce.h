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
