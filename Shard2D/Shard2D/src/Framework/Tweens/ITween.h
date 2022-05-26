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
		/*
			Automatically deallocate the tween at the end of the animation (if the repeat is infinite, it will auto delete at the stop).

			@param selfDelete:		If the tween have to be auto deleted.
		*/
		virtual ITween* SelfDelete(bool selfDelete = true) = 0;

		virtual bool IsEqual(ITween* otherTween) = 0;
		virtual bool IsOverridable(ITween* otherTween) = 0;

	protected:
		/*
			Called each frame to update the tween if active.
		*/
		virtual void UpdateValue(float deltaTime) = 0;

		virtual void SetupForStart() = 0;

		virtual bool GetSelfDelete() = 0;

	};
}