#include "TweenActuator.h"
#pragma once

namespace Shard2D
{
	template<typename T>
	TweenActuator<T>::TweenActuator(T& newValue, T newTargetValue, float newDuration)
		: _value(newValue), _start(newValue), _target(newTargetValue), _totalDuration(newDuration) { }

	template<typename T>
	TweenActuator<T>::~TweenActuator() { }

	template<typename T>
	ITween* TweenActuator<T>::Delay(float delay)
	{
		_delay = delay;
		return this;
	}

	template<typename T>
	ITween* TweenActuator<T>::Ease()
	{
		return this;
	}

	template<typename T>
	ITween* TweenActuator<T>::Reflect(bool reflect)
	{
		_reflect = reflect;
		return this;
	}

	template<typename T>
	ITween* TweenActuator<T>::Repeat(int times)
	{
		_repeat = times;
		return this;
	}

	template<typename T>
	void TweenActuator<T>::UpdateValue()
	{

	}
}