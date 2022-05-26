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
		if (interruptActiveTween)
			CheckOverridableTweens(tween);

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

	void TweensManager::AddTweenToDeletionList(ITween* tween)
	{
		_destroyableTweens.push_back(tween);
	}

	void TweensManager::DeleteTweenAnimation(ITween* tween)
	{
		int count = 0;
		for (ITween* _tween : _createdTweens)
		{
			if (tween == _tween)
			{
				_createdTweens.erase(_createdTweens.begin() + count);
				delete _tween;
				return;
			}
			count++;
		}
	}

	void TweensManager::StopTweenAnimation(ITween* tween, bool runCompleteEvent)
	{
		if (FindTween(tween))
		{
			if (runCompleteEvent)
				tween->DispatchEvent<TweenEvent>(TweenEvent::OnComplete);
			RemoveTween(tween);
		}
	}

	void TweensManager::UpdateTweens()
	{
		for (ITween* actualTween : _activeTweens)
			if(actualTween != nullptr)
				actualTween->UpdateValue(M_ClockManager->GetDeltaTime());

		for (ITween* tween : _destroyableTweens)
		{
			if (tween != nullptr)
				DeleteTweenAnimation(tween);
		}
		_destroyableTweens.clear();
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
				if (tween->GetSelfDelete())
					DeleteTween(tween);
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
	void TweensManager::CheckOverridableTweens(ITween* tween)
	{
		for (ITween* actualTween : _activeTweens)
		{
			if (actualTween->IsOverridable(tween))
			{
				RemoveTween(actualTween);
			}
		}
	}
}
