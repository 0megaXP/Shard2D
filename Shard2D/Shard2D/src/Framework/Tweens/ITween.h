#pragma once

#include "../Events/EventDispatcher.h"
#include "Easing/IEasing.h"

namespace Shard2D
{
	class ITween : public EventDispatcher
	{
	protected:
		ITween();
		~ITween();

		friend class TweensManager;

	public:
		virtual ITween* Delay(float delay, bool onRepeat = false) = 0;
		virtual ITween* Ease(EaseType::Type ease) = 0;
		virtual ITween* Reflect(bool reflect = true) = 0;
		virtual ITween* Repeat(int times) = 0;

	protected:
		virtual void UpdateValue(float deltaTime) = 0;

		virtual void SetupForStart() = 0;

	};
}