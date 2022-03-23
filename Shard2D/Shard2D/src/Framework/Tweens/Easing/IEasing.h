#pragma once

#include "../../Utils/ShardUtils.h"

namespace Shard2D
{
	namespace EaseType
	{
		typedef enum 
		{
			Linear,
			SineIn,		SineOut,	SineInOut,
			QuadIn,		QuadOut,	QuadInOut,
			CubicIn,	CubicOut,	CubicInOut,
			QuartIn,	QuartOut,	QuartInOut,
			QuintIn,	QuintOut,	QuintInOut,
			ExpoIn,		ExpoOut,	ExpoInOut,
			CircIn,		CircOut,	CircInOut,
			BackIn,		BackOut,	BackInOut,
			ElasticIn,	ElasticOut,	ElasticInOut,
			BounceIn,	BounceOut,	BounceInOut
		} Type;
	}

	class IEasing
	{
	public:
		IEasing() {};
		~IEasing() {};

		virtual double Calculate(double k) = 0;
	};
}