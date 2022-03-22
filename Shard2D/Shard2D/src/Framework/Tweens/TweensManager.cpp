#include "TweensManager.h"

#include "../Utils/CustomIOStream.h"
#include "../Events/EventTypes/TweenEvent.h"
#include "Easing/Sine.h"
#include "Easing/Linear.h"
#include "../Management/Managers.h"

namespace Shard2D
{
	TweensManager::TweensManager()
	{

	}

	TweensManager::~TweensManager()
	{
		for (ITween* _tween : _createdTweens)
			delete _tween;

		Log("Tweens Manager destroyed!", TextColor::Green);
	}

	void TweensManager::StartTween(ITween* tween, bool interruptActiveTween)
	{
		if (!FindTween(tween))
		{
			_activeTweens.push_back(tween);
			tween->SetupForStart();
		}
		else if(interruptActiveTween)
		{
			tween->SetupForStart();
		}
	}

	void TweensManager::StopTween(ITween* tween, bool runCompleteEvent)
	{
		if (FindTween(tween))
		{
			RemoveTween(tween);
			if (runCompleteEvent)
				tween->DispatchEvent<TweenEvent>(TweenEvent::OnComplete);
		}
	}

	void TweensManager::UpdateTweens()
	{
		for (ITween* actualTween : _activeTweens)
		{
			actualTween->UpdateValue(M_ClockManager->GetDeltaTime());
		}
	}

	void TweensManager::TweenCompleted(TweenEvent* _event)
	{
		ITween* tweenCompleted = static_cast<ITween*>(_event->GetTarget());
		RemoveTween(tweenCompleted);
	}

	double TweensManager::GetEaseCalculation(EaseType::Type easeType, double k)
	{
		switch (easeType)
		{
		case EaseType::Linear:		return Linear::Calculate(k);
			break;
		case EaseType::SineIn:		return SineIn::Calculate(k);
			break;
		case EaseType::SineOut:		return SineOut::Calculate(k);
			break;
		case EaseType::SineInOut:	return SineInOut::Calculate(k);
			break;
		default:					return Linear::Calculate(k);
			break;
		}
	}

	void TweensManager::RemoveTween(ITween* tween)
	{
		int count = 0;
		for (ITween* actualTween : _activeTweens)
		{
			if (actualTween == tween)
			{
				_activeTweens.erase(_activeTweens.begin() + count);
				return;
			}
			count++;
		}
	}

	bool TweensManager::FindTween(ITween* tween)
	{
		for (ITween* actualTween : _activeTweens)
		{
			if (actualTween == tween)
			{
				return true;
			}
		}

		return false;
	}
}
