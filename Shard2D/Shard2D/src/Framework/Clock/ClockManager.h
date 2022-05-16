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

		float FPS;
		std::vector<float> fpsSaved;
		int frameToSave = 10;
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