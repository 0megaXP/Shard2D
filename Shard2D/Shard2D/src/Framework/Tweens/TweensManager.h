#pragma once

#include <vector>
#include <memory>

#include "Easing/IEasing.h"

namespace Shard2D
{
	class ITween;
	class TweenEvent;

	class TweensManager
	{
	private:
		TweensManager();

		~TweensManager();

		friend class Managers;
		friend class GameManager;

	private:
		std::vector<ITween*> _activeTweens;
		std::vector<ITween*> _createdTweens;
		
	public:
		template<typename T>
		ITween* CreateTween(T& value, T targetValue, float duration);

		void StartTween(ITween* tween, bool interruptActiveTween = false);

		void StopTween(ITween* tween, bool runCompleteEvent = false);

		double GetEaseCalculation(EaseType::Type easeType, double k);

	private:
		void UpdateTweens();

		void TweenCompleted(TweenEvent* _event);

		void RemoveTween(ITween* tween);
		bool FindTween(ITween* tween);
	};
}

#include "TweensManager.tpp"