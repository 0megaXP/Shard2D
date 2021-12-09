#pragma once

#include <stdint.h>

class GameManager;

class ClockManager
{
public:
	ClockManager();
	~ClockManager();

	friend class GameManager;

private:
	float _deltaTime = 0;
	float _startTick = 0;

	int _frameRateCap = 240;
	uint64_t _startFrameCounter;

public:
	float GetDeltaTime();
	float GetDeltaTimeMS();

private:
	void UpdateDeltaTime();
	void NewFrame();
	void ManageFramesCap();
};

