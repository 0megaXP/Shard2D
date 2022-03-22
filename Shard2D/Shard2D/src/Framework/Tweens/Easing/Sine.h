#pragma once

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class SineIn : public IEasing
	{
	public:
		SineIn() { };

		static double Calculate(double k)
		{
			return 1 - cos(k * (M_PI / 2));;
		}
	};

	class SineOut : public IEasing
	{
	public:
		SineOut() { };

		static double Calculate(double k)
		{
			return sin(k * (M_PI / 2));;
		}
	};

	class SineInOut : public IEasing
	{
	public:
		SineInOut() { };

		static double Calculate(double k)
		{
			return -(cos(M_PI * k) - 1) / 2;
		}
	};
}