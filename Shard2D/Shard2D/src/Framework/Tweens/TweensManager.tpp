#include "Tween.h"

namespace Shard2D
{
	template<typename T>
	Tween* TweensManager::CreateTween(T& value)
	{
		Tween* newTween = new Tween();
		_createdTweens.push_back(newTween);
		return newTween;
	}
}