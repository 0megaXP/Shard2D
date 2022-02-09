#include "ClockManager.h"

#include <SDL.h>

#include "../Utils/ShardUtils.h"

ClockManager::ClockManager()
    : _deltaTime(0)
{
    Log("ClockManager created!", TextColor::Yellow);
    
    NewFrame();
}

ClockManager::~ClockManager()
{
    Log("ClockManager destroyed!", TextColor::Yellow);
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

float ClockManager::GetFPS()
{
    return FPS;
}

/**
 Called frame by frame from the GameManager for the delta time update
 */
void ClockManager::UpdateDeltaTime()
{
    _deltaTime = SDL_GetTicks() - _startTick;
    UpdateFPS();

    //std::cout << "FPS: " << ((1 / _deltaTime) * 1000) << "\n";
    //std::cout << "Previous time: " << _previousTick << "\n";
    //std::cout << "Current time: " << _currentTick << "\n";
    //std::cout << "Delta time: " << GetDeltaTimeMS() << "\n";
}

void ClockManager::NewFrame()
{
    _startTick = float(SDL_GetTicks());
    _startFrameCounter = SDL_GetPerformanceCounter();
}

void ClockManager::ManageFramesCap()
{
    float elapsedMS = (SDL_GetPerformanceCounter() - _startFrameCounter) / SDL_GetPerformanceFrequency() * 1000.0f;

    SDL_Delay(floor((1000 / (_frameRateCap + _frameRateCap / 4)) - elapsedMS));
}

void ClockManager::UpdateFPS()
{
    if (fpsCount < frameToSave)
    {
        fpsSaved.push_back((1 / _deltaTime) * 1000);
        fpsCount++;
    }
    else
    {
        float sum = 0;
        for (int i = 0; i < fpsCount; i++)
            sum += fpsSaved[i];

        FPS = sum / frameToSave;

        fpsCount = 0;
        fpsSaved.clear();
    }
}
