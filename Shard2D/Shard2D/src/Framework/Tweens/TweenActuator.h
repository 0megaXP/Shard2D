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

#pragma once

#include "ITween.h"

namespace Shard2D
{
	template<typename T>
	class TweenActuator : public ITween
	{
	protected:
		TweenActuator(T& newValue, T newTargetValue, float newDuration);
		~TweenActuator();

		friend class TweensManager;

	protected:
		T& _value;	// The reference to the value to animate
		T _start;	// The starting value saved from the reference value
		T _target;	// The target value of the animation
		float _totalDuration;
		float _delay = 0;
		EaseType::Type _ease = EaseType::Linear;
		bool _reflect = false;
		int _repeat = 0;
		bool _selfDelete = false;

	private:
		float _distanceToCover = 0;
		float _actualDuration = 0;
		T _actualStart;	// The starting point used as placeholder for not changing the real one
		bool _delayOnRepeat = false;	// If the delay affects the repeated animations
		bool _onDelay = false;	// If the actual tween is on delay
		int _repeatCount = 0;
		bool _reflecting = false;	// If the actual animation is a reflection
		float _deltaDifference = 0;	// Used for concatenate correctly the repeated animation with the previous delta time


	public:
		// Inteface functions
		ITween* Delay(float delay, bool onRepeat = false);
		ITween* Ease(EaseType::Type ease);
		ITween* Reflect(bool reflect);
		ITween* Repeat(int times);
		ITween* SelfDelete(bool selfDelete = true);
		
		bool operator==(TweenActuator<T>& otherTween);
		bool IsEqual(ITween* otherTween);
		bool IsOverridable(ITween* otherTween);

	protected:

		// Inteface functions
		void UpdateValue(float deltaTime);
		void SetupForStart();
		bool GetSelfDelete();

		/*
			Setup all values for the repeat animations		
		*/
		void SetupForRepeat();
		/*
			When the animation is completed, this function manages the post animation conditions
		*/
		void TweenPhaseCompleted();
	};
}

#include "TweenActuator.tpp"