#include "TweenActuator.h"

#include "../Management/Managers.h"

namespace Shard2D
{
	template<typename T>
	TweenActuator<T>::TweenActuator(T& newValue, T newTargetValue, float newDuration)
		: _value(newValue), _start(newValue), _target(newTargetValue), _totalDuration(newDuration) 
	{

	}

	template<typename T>
	TweenActuator<T>::~TweenActuator() 
	{
		Log("Tween Actuator destroyed!", TextColor::Aqua);
	}

	template<typename T>
	ITween* TweenActuator<T>::Delay(float delay)
	{
		_delay = delay;
		return this;
	}

	template<typename T>
	ITween* TweenActuator<T>::Ease(EaseType::Type ease)
	{
		_ease = ease;
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
	void TweenActuator<T>::UpdateValue(float deltaTime)
	{
		_actualDuration += deltaTime +_deltaDifference;
		_deltaDifference = 0;
		// k is the time value used during the ease calculation
		float k = _actualDuration > 0 ? _actualDuration / _totalDuration : 0;
		if (k > _totalDuration)
		{
			_deltaDifference = k - _totalDuration;
			k = _totalDuration;
		}

		double incrementNormalized = Managers::tweensManager->GetEaseCalculation(_ease, k);
		float increment = incrementNormalized * _distanceToCover;
		Log(incrementNormalized, TextColor::Red);

		_value = _start + increment;

		if (k >= 1)
			DispatchEvent<TweenEvent>(TweenEvent::OnComplete);
	}

	template<typename T>
	void TweenActuator<T>::SetupForStart()
	{
		_actualDuration = 0;
		_repeatCount = 0;
		_reflecting = false;
		_start = _value;
		_distanceToCover = _target - _start;
	}
}