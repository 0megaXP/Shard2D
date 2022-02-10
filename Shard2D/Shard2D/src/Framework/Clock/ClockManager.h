#pragma once

#include <stdint.h>
#include <vector>

class ClockManager
{
public:
	ClockManager();
	~ClockManager();

	friend class GameManager;

private:
	float _deltaTime = 0;
	float _startTick = 0;

	int _frameRateCap = 60;
	uint64_t _startFrameCounter;

	float FPS;
	std::vector<float> fpsSaved;
	int frameToSave = 30;
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

private:
	void UpdateDeltaTime();
	void NewFrame();
	void ManageFramesCap();

	void UpdateFPS();
};

