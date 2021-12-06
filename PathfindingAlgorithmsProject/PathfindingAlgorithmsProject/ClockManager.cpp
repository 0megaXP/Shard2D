#include "ClockManager.h"

#include <SDL.h>
#include <iostream>

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

/**
Return the actual frame's delta time
*/
float ClockManager::GetDeltaTime()
{
    return _deltaTime;
}

/**
 Called frame by frame from the GameManager for the delta time update
 */
void ClockManager::UpdateDeltaTime()
{
    if (_currentTick != _previousTick)
    {
        _previousTick = _currentTick;
        _currentTick = SDL_GetTicks();

        _deltaTime = (_currentTick - _previousTick) / 1000.0f;
    }
    else
    {
        std::cout << "Wrong delta update!";
    }
}
