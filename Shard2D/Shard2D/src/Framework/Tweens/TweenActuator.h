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
		T& _value;
		T _start;
		T _target;
		float _totalDuration;
		float _delay = 0;
		//Ease
		bool _reflect = false;
		int _repeat = 0;

	private:
		float _actualDuration = 0;
		int _repeatCount = 0;


	public:
		ITween* Delay(float delay);
		ITween* Ease(/*ease*/);
		ITween* Reflect(bool reflect);
		ITween* Repeat(int times);

	protected:

		void UpdateValue();
	};
}

#include "TweenActuator.tpp"