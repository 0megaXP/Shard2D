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
		/*
			Applies a delay to the tween. This delay can be applied only at the beginning of the tween or at each Repeat.

			@param delay:			The duration of the delay in seconds.
			@param onRepeat:		If the delay must be applied at each Repeat of the Tween.
		*/
		virtual ITween* Delay(float delay, bool onRepeat = false) = 0;
		/*
			Sets the ease of the tween.

			@param ease:			The ease type to apply. You can set this enum including the IEasing interface and using the EaseType enum.
		*/
		virtual ITween* Ease(EaseType::Type ease) = 0;
		/*
			Applies a repeat count to the tween. At the end, if this value is greater than 1, the tween will repeat the same animation as many times as the value.

			@param times:			The number of times the tween will repeat the animation. If the value is -1, the animation is repeated indefinetly.
		*/
		virtual ITween* Repeat(int times) = 0;
		/*
			Manage the repeat animation as a reflection, reversing the starting and ending values.

			@param reflect:			If the reflection is active.
		*/
		virtual ITween* Reflect(bool reflect = true) = 0;

	protected:
		/*
			Called each frame to update the tween if active.
		*/
		virtual void UpdateValue(float deltaTime) = 0;

		virtual void SetupForStart() = 0;

	};
}