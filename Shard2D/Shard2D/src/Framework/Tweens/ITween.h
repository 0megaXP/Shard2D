#pragma once

#include "../Events/EventDispatcher.h"

namespace Shard2D
{
	class ITween : public EventDispatcher
	{
	protected:
		ITween();
		~ITween();

		friend class TweensManager;

	public:
		virtual ITween* Delay(float delay) = 0;
		virtual ITween* Ease(/*ease*/) = 0;
		virtual ITween* Reflect(bool reflect) = 0;
		virtual ITween* Repeat(int times) = 0;

	protected:
		virtual void UpdateValue() = 0;

	};
}