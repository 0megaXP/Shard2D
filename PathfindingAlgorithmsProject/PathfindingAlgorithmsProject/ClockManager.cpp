#include "ClockManager.h"
#include <SDL.h>

float ClockManager::_deltaTime = 0;

ClockManager::ClockManager()
{
    _currentTick = 0;
    _previousTick = 0;
    _deltaTime = 0;
}

ClockManager::~ClockManager()
{
}

float ClockManager::GetDeltaTime()
{
    return _deltaTime;
}

void ClockManager::UpdateDeltaTime()
{
    _previousTick = _currentTick;
    _currentTick = SDL_GetTicks();

    _deltaTime = (_currentTick - _previousTick) / 1000.0f;
}
