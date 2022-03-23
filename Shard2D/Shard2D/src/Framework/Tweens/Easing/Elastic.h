#pragma once

#include <math.h>
#include <SDL_stdinc.h>

#include "IEasing.h"

namespace Shard2D
{
	class ElasticIn : public IEasing
	{
	public:
		ElasticIn() { };

		static double Calculate(double k)
		{
			if (k == 0)
				return 0;
			else
				if (k == 1)
					return 1;
				else
					return -pow(2, 10 * k - 10) * sin((k * 10 - 10.75) * ((2 * M_PI) / 3));
		}
	};

	class ElasticOut : public IEasing
	{
	public:
		ElasticOut() { };

		static double Calculate(double k)
		{
			if (k == 0)
				return 0;
			else
				if (k == 1)
					return 1;
				else
					return pow(2, -10 * k) * sin((k * 10 - 0.75) * ((2 * M_PI) / 3)) + 1;
		}
	};

	class ElasticInOut : public IEasing
	{
	public:
		ElasticInOut() { };

		static double Calculate(double k)
		{
			if (k == 0)
				return 0;
			else
				if (k == 1)
					return 1;
				else if(k < 0.5)
					return -(pow(2, 20 * k - 10) * sin((20 * k - 11.125) * ((2 * M_PI) / 4.5))) / 2;
				else
					return (pow(2, -20 * k + 10) * sin((20 * k - 11.125) * ((2 * M_PI) / 4.5))) / 2 + 1;
		}
	};
}