#include "ClockManager.h"

#include <SDL.h>
#include <iostream>

ClockManager::ClockManager()
{
    _currentTick = 0;
    _previousTick = SDL_GetTicks();
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
    return _deltaTime / 1000;
}

float ClockManager::GetDeltaTimeMS()
{
    return _deltaTime;
}

/**
 Called frame by frame from the GameManager for the delta time update
 */
void ClockManager::UpdateDeltaTime()
{
    if (SDL_GetTicks() != _previousTick)
    {
        _previousTick = _currentTick;
        _currentTick = SDL_GetTicks();
        _deltaTime = _currentTick - _previousTick;

        //std::cout << "FPS: " << ((1 / _deltaTime) * 1000) << "\n";
        //std::cout << "Previous time: " << _previousTick << "\n";
        //std::cout << "Current time: " << _currentTick << "\n";
        //std::cout << "Delta time: " << GetDeltaTimeMS() << "\n";
    }
    else
    {
        std::cout << "Wrong delta update! \n";
    }
}
