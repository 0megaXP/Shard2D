#include "ClockManager.h"

#include <SDL.h>
#include <iostream>

ClockManager::ClockManager()
{
    NewFrame();
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
    _deltaTime = SDL_GetTicks() - _startTick;

    //std::cout << "FPS: " << ((1 / _deltaTime) * 1000) << "\n";
    //std::cout << "Previous time: " << _previousTick << "\n";
    //std::cout << "Current time: " << _currentTick << "\n";
    //std::cout << "Delta time: " << GetDeltaTimeMS() << "\n";
}

void ClockManager::NewFrame()
{
    _startTick = SDL_GetTicks();
    _startFrameCounter = SDL_GetPerformanceCounter();
}

void ClockManager::ManageFramesCap()
{
    float elapsedMS = (SDL_GetPerformanceCounter() - _startFrameCounter) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

    SDL_Delay(floor((1000 / _frameRateCap) - elapsedMS));
}
