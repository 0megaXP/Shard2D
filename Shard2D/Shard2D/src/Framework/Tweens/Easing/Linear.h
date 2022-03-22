#pragma once

#include "IEasing.h"

namespace Shard2D
{
	class Linear : public IEasing
	{
	public:
		Linear() { };

		static double Calculate(double k)
		{
			return k;
		}
	};
}