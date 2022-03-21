#pragma once

namespace Shard2D
{
	template<typename T>
	TweenActuator<T>::TweenActuator(T& newValue, T newTargetValue, float newDuration)
		: _value(newValue), _target(newTargetValue), _totalDuration(newDuration)
	{

	}
	template<typename T>
	TweenActuator<T>::~TweenActuator()
	{
	}
	template<typename T>
	void TweenActuator<T>::UpdateValue()
	{
	}
}