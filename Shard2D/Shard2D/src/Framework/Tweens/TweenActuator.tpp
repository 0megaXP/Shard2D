/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "TweenActuator.h"

#include "../Management/Managers.h"

namespace Shard2D
{
	template<typename T>
	TweenActuator<T>::TweenActuator(T& newValue, T newTargetValue, float newDuration)
		: _value(newValue), _start(newValue), _target(newTargetValue), _totalDuration(newDuration), _actualStart(newValue) {}

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
	ITween* TweenActuator<T>::SelfDelete(bool selfDelete)
	{
		_selfDelete = selfDelete;
		return this;
	}

	template<typename T>
	bool TweenActuator<T>::operator==(TweenActuator<T>& otherTween)
	{
		return	&_value == &(otherTween._value) &&
				_target == otherTween._target &&
				_totalDuration == otherTween._totalDuration &&
				_delay == otherTween._delay &&
				_ease == otherTween._ease && 
				_reflect == otherTween._reflect && 
				_repeat == otherTween._repeat &&
				_selfDelete == otherTween._selfDelete;
	}

	template<typename T>
	bool TweenActuator<T>::IsEqual(ITween* otherTween)
	{
		TweenActuator<T>* castedTween = static_cast<TweenActuator<T>*>(otherTween);
		if (castedTween != nullptr)
			return *this == *castedTween;
		else
			return false;
	}

	template<typename T>
	bool TweenActuator<T>::IsOverridable(ITween* otherTween)
	{
		TweenActuator<T>* castedTween = static_cast<TweenActuator<T>*>(otherTween);
		if (castedTween != nullptr)
			return this == castedTween || (&_value == &(castedTween->_value));
		else
			return false;
	}

	template<typename T>
	void TweenActuator<T>::UpdateValue(float deltaTime)
	{
		_actualDuration += deltaTime + _deltaDifference;
		_deltaDifference = 0;
		// If the tween has a delay, set the start at the end of it
		if (_onDelay)
		{
			if (_actualDuration > 0)
			{
				_onDelay = false;
				_start = _value;
				_actualStart = _value;
				_distanceToCover = _target - _start;
			}
		}

		// k is the time value used during the ease calculation
		float k = _actualDuration > 0 ? _actualDuration / _totalDuration : 0;
		if (k > 1)
		{
			_deltaDifference = _totalDuration - _actualDuration;
			k = 1;
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
		// The delay is applied directly to the duration as negative value
		_actualDuration = _delay > 0 ? -_delay : 0;
		_onDelay = _actualDuration < 0;
		_repeatCount = 1;
		_reflecting = false;
		_start = _value;
		_actualStart = _value;
		_distanceToCover = _target - _start;
	}

	template<typename T>
	bool TweenActuator<T>::GetSelfDelete()
	{
		return _selfDelete;
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