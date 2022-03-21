#include "TweenActuator.h"

namespace Shard2D
{
	template<typename T>
	ITween* TweensManager::CreateTween(T& value, T targetValue, float duration)
	{
		ITween* newTween = new TweenActuator<T>(value, targetValue, duration);
		_createdTweens.push_back(newTween);
		return newTween;
	}
}