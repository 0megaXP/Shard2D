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
		T _target;
		float _totalDuration;
		float _actualDuration;

		void UpdateValue();
	};
}

#include "TweenActuator.tpp"