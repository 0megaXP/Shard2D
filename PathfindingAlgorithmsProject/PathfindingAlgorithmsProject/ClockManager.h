#pragma once
class ClockManager
{
public:
	ClockManager();
	~ClockManager();

private:
	static float _deltaTime;
	float _currentTick = 0;
	float _previousTick = 0;

public:
	static float GetDeltaTime();
	void UpdateDeltaTime();
};

