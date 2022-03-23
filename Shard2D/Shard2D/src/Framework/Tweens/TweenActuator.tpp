#include "TweenActuator.h"

#include "../Management/Managers.h"

namespace Shard2D
{
	template<typename T>
	TweenActuator<T>::TweenActuator(T& newValue, T newTargetValue, float newDuration)
		: _value(newValue), _start(newValue), _target(newTargetValue), _totalDuration(newDuration), _actualStart(newValue)
	{

	}

	template<typename T>
	TweenActuator<T>::~TweenActuator() 
	{
		Log("Tween Actuator destroyed!", TextColor::Aqua);
	}

	template<typename T>
	ITween* TweenActuator<T>::Delay(float delay, bool onRepeat)
	{
		_delay = delay;
		_delayOnRepeat = onRepeat;
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
		_actualDuration += deltaTime + _deltaDifference;
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

		if (k > 0)
			_value = _actualStart + increment;

		// Tween phase completed
		if (k >= 1)
			TweenPhaseCompleted();
	}

	template<typename T>
	void TweenActuator<T>::SetupForStart()
	{
		_actualDuration = _delay > 0 ? -_delay : 0;
		_repeatCount = 1;
		_reflecting = false;
		_start = _value;
		_actualStart = _value;
		_distanceToCover = _target - _start;
	}

	template<typename T>
	void TweenActuator<T>::SetupForRepeat()
	{
		if(_delayOnRepeat)
			_actualDuration = _delay > 0 ? -_delay : 0;
		else
			_actualDuration = 0;

		_repeatCount++;

		if (_reflect)
		{
			_reflecting = !_reflecting;
			if (_reflecting)
			{
				_actualStart = _target;
				_distanceToCover = _start - _target;
			}
			else
			{
				_actualStart = _value;
				_distanceToCover = _target - _start;
			}
		}
	}

	template<typename T>
	void TweenActuator<T>::TweenPhaseCompleted()
	{
		if (_repeatCount < _repeat || _repeat == -1)
			SetupForRepeat();
		else
			DispatchEvent<TweenEvent>(TweenEvent::OnComplete);
	}
}