#include "TweenActuator.h"

#include "../Events/EventTypes/TweenEvent.h"

namespace Shard2D
{
	template<typename T>
	ITween* TweensManager::CreateTweenAnimation(T& value, T targetValue, float duration)
	{
		ITween* newTween = new TweenActuator<T>(value, targetValue, duration);
		_createdTweens.push_back(newTween);
		newTween->AddEventListener<TweenEvent, TweensManager>(TweenEvent::OnComplete, &TweensManager::TweenCompleted, this);
		return newTween;
	}
}