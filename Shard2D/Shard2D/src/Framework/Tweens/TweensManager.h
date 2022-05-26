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

#include <vector>
#include <memory>

#include "Easing/IEasing.h"

namespace Shard2D
{
	/*
			Creates and returns a tween value as ITween ptr. You should always create tweens with this function for a better memory management. Once created, you must store the tween inside
			an ITween ptr value and setup it with its functions. The tween doesn't start with this function. You have to call the StartTween functon from the TweensManager.

			@param value:			The value to animate.
			@param targetValue:		The target value of the animation.
			@param duration:		The duration of the animation in seconds.
		*/
#define CreateTween Managers::tweensManager->CreateTweenAnimation
	/*
		Set the tween as active and start to update its value. If the tween is already running, you can decide if overwrite it or delete the start function and let the previous animation to
		carry on.

		@param tween:			The tween to start.
		@param interruptActiveTween:	If the already running tween must be interrupted and restarted from the beginnning (the default value is false).
	*/
#define StartTween Managers::tweensManager->StartTweenAnimation
	/*
		Stops immediatly the tween animation and removes it from the active tweens. You can decide to still run the complete event.

		@param tween:			The tween to stop.
		@param runCompleteEvent:	If the complete event must stil be called (the default value is false).
	*/
#define StopTween Managers::tweensManager->StopTweenAnimation
	/*
		Delete the reference of an ITween ptr. If you are sure to never use a tween anymore, call this function to deallocate its memory.

		@param tween:			The tween to delete.
	*/
#define DeleteTween Managers::tweensManager->AddTweenToDeletionList


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
		std::vector<ITween*> _createdTweens;	// Contains all the created tweens and deallocate all of them in the destructor
		std::vector<ITween*> _destroyableTweens;
		
	public:
		/*
			Creates and returns a tween value as ITween ptr. You should always create tweens with this function for a better memory management. Once created, you must store the tween inside
			an ITween ptr value and setup it with its functions. The tween doesn't start with this function. You have to call the StartTween functon from the TweensManager.

			@param value:			The value to animate.
			@param targetValue:		The target value of the animation.
			@param duration:		The duration of the animation in seconds.
		*/
		template<typename T>
		ITween* CreateTweenAnimation(T& value, T targetValue, float duration);
		/*
			Set the tween as active and start to update its value. If the tween is already running, you can decide if overwrite it or delete the start function and let the previous animation to
			carry on.

			@param tween:			The tween to start.
			@param interruptActiveTween:	If the already running tween must be interrupted and restarted from the beginnning (the default value is false).
		*/
		void StartTweenAnimation(ITween* tween, bool interruptActiveTween = false);
		/*
			Delete the reference of an ITween ptr. If you are sure to never use a tween anymore, call this function to deallocate its memory.

			@param tween:			The tween to delete.
		*/
		void AddTweenToDeletionList(ITween* tween);
		/*
			Stops immediatly the tween animation and removes it from the active tweens. You can decide to still run the complete event.

			@param tween:			The tween to stop.
			@param runCompleteEvent:	If the complete event must stil be called (the default value is false).
		*/
		void StopTweenAnimation(ITween* tween, bool runCompleteEvent = false);
		/*
			Returns the value from the ease calculation based on the easeType and the k value passed.
		*/
		double GetEaseCalculation(EaseType::Type easeType, double k);

	private:
		void UpdateTweens();

		void TweenCompleted(TweenEvent* _event);

		void RemoveTween(ITween* tween);
		void DeleteTweenAnimation(ITween* tween);
		bool FindTween(ITween* tween);
		void CheckOverridableTweens(ITween* tween);
	};
}

#include "TweensManager.tpp"