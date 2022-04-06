#include "TweensManager.h"

#include "../Utils/CustomIOStream.h"
#include "../Management/Managers.h"
#include "../Events/EventTypes/TweenEvent.h"
#include "Easing/Linear.h"
#include "Easing/Sine.h"
#include "Easing/Quad.h"
#include "Easing/Cubic.h"
#include "Easing/Quart.h"
#include "Easing/Quint.h"
#include "Easing/Expo.h"
#include "Easing/Circ.h"
#include "Easing/Back.h"
#include "Easing/Elastic.h"
#include "Easing/Bounce.h"

namespace Shard2D
{
	TweensManager::TweensManager() {}

	TweensManager::~TweensManager()
	{
		for (ITween* _tween : _createdTweens)
			delete _tween;

		Log("Tweens Manager destroyed!", TextColor::Green);
	}

	void TweensManager::StartTweenAnimation(ITween* tween, bool interruptActiveTween)
	{
		if (!FindTween(tween))
		{
			_activeTweens.push_back(tween);
			tween->SetupForStart();
		}
		else if (interruptActiveTween)
		{
			tween->SetupForStart();
		}
	}

	void TweensManager::StopTweenAnimation(ITween* tween, bool runCompleteEvent)
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
			actualTween->UpdateValue(M_ClockManager->GetDeltaTime());
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
		case EaseType::Linear:			return Linear::Calculate(k);
		case EaseType::SineIn:			return SineIn::Calculate(k);
		case EaseType::SineOut:			return SineOut::Calculate(k);
		case EaseType::SineInOut:		return SineInOut::Calculate(k);
		case EaseType::QuadIn:			return QuadIn::Calculate(k);
		case EaseType::QuadOut:			return QuadOut::Calculate(k);
		case EaseType::QuadInOut:		return QuadInOut::Calculate(k);
		case EaseType::CubicIn:			return CubicIn::Calculate(k);
		case EaseType::CubicOut:		return CubicOut::Calculate(k);
		case EaseType::CubicInOut:		return CubicInOut::Calculate(k);
		case EaseType::QuartIn:			return QuartIn::Calculate(k);
		case EaseType::QuartOut:		return QuartOut::Calculate(k);
		case EaseType::QuartInOut:		return QuartInOut::Calculate(k);
		case EaseType::QuintIn:			return QuintIn::Calculate(k);
		case EaseType::QuintOut:		return QuintOut::Calculate(k);
		case EaseType::QuintInOut:		return QuintInOut::Calculate(k);
		case EaseType::ExpoIn:			return ExpoIn::Calculate(k);
		case EaseType::ExpoOut:			return ExpoOut::Calculate(k);
		case EaseType::ExpoInOut:		return ExpoInOut::Calculate(k);
		case EaseType::CircIn:			return CircIn::Calculate(k);
		case EaseType::CircOut:			return CircOut::Calculate(k);
		case EaseType::CircInOut:		return CircInOut::Calculate(k);
		case EaseType::BackIn:			return BackIn::Calculate(k);
		case EaseType::BackOut:			return BackOut::Calculate(k);
		case EaseType::BackInOut:		return BackInOut::Calculate(k);
		case EaseType::ElasticIn:		return ElasticIn::Calculate(k);
		case EaseType::ElasticOut:		return ElasticOut::Calculate(k);
		case EaseType::ElasticInOut:	return ElasticInOut::Calculate(k);
		case EaseType::BounceIn:		return BounceIn::Calculate(k);
		case EaseType::BounceOut:		return BounceOut::Calculate(k);
		case EaseType::BounceInOut:		return BounceInOut::Calculate(k);
		default:						return Linear::Calculate(k);
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
