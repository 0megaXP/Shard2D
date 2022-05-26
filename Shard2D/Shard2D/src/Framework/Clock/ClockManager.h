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

#include <stdint.h>
#include <vector>
#include <chrono>
#include <thread>

namespace Shard2D
{
	class ClockManager
	{
	private:
		ClockManager();
		~ClockManager();

		friend class Managers;
		friend class GameManager;

		float _deltaTime = 0;

		bool _frameRateCapEnabled = false;
		int _frameRateCap = 60;
		std::chrono::system_clock::time_point _startFrameCounter = std::chrono::system_clock::now();
		int _adjuster = 0;

		float FPS;
		std::vector<float> fpsSaved;
		int frameToSave = 60;
		int fpsCount = 0;

	public:
		/*
		Returns the normalized delta time of the previous frame. Used to adapt any change in a value to the current frame rate
		*/
		float GetDeltaTime();

		/*
		Returns the real delta time of the previous frame. The real delta time is the duration of the previous frame
		*/
		float GetDeltaTimeMS();

		/*
		Returns the FPS calculated with the actual delta time
		*/
		float GetFPS();
		/*
		Enable a frame rate cap for the app.
		@param newFrameRate: The new frame rate cap (must be greater than 0).
		*/
		void EnableFrameRateCap(int newFrameRate);
		/*
		Disable a previous settled frame rate cap.
		*/
		void DisableFrameRateCap();

	private:
		void NewFrame();
		void ManageFramesCap();

		void UpdateFPS();
	};
}