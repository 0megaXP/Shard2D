#pragma once
class ClockManager
{
public:
	ClockManager();
	~ClockManager();

private:
	float _deltaTime = 0;
	float _currentTick = 0;
	float _previousTick = 0;

public:
	float GetDeltaTime();
	float GetDeltaTimeMS();
	void UpdateDeltaTime();
};

