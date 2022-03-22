#pragma once

#include "../../Utils/ShardUtils.h"

namespace Shard2D
{
	namespace EaseType
	{
		typedef enum 
		{
			Linear,
			SineIn,
			SineOut,
			SineInOut
		} Type;
	}

	class IEasing
	{
	public:
		IEasing() {};
		~IEasing() {};

		virtual double Calculate(double k) = 0;

	protected:
		virtual void SetupForStart() = 0;
	};
}