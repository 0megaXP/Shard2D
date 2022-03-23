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
		EaseType::Type _ease = EaseType::Linear;
		bool _reflect = false;
		int _repeat = 0;

	private:
		float _distanceToCover = 0;
		float _actualDuration = 0;
		T _actualStart;
		bool _delayOnRepeat = false;
		int _repeatCount = 0;
		bool _reflecting = false;
		float _deltaDifference = 0;


	public:
		ITween* Delay(float delay, bool onRepeat = false);
		ITween* Ease(EaseType::Type ease);
		ITween* Reflect(bool reflect);
		ITween* Repeat(int times);

	protected:

		void UpdateValue(float deltaTime);

		void SetupForStart();

		void SetupForRepeat();

		void TweenPhaseCompleted();
	};
}

#include "TweenActuator.tpp"