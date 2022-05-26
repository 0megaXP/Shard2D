/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ClockManager.h"

#include <SDL.h>

#include "../Utils/ShardUtils.h"

namespace Shard2D
{
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

    void ClockManager::EnableFrameRateCap(int newFrameRate)
    {
        if (newFrameRate > 0)
        {
            _frameRateCapEnabled = true;
            _frameRateCap = newFrameRate;
        }
        else
        {
            _frameRateCapEnabled = false;
        }
    }

    void ClockManager::DisableFrameRateCap()
    {
        _frameRateCapEnabled = false;
    }

    void ClockManager::NewFrame()
    {
        ManageFramesCap();
        _startFrameCounter = std::chrono::system_clock::now();
    }

    void ClockManager::ManageFramesCap()
    {
        // Save the end frame time
        std::chrono::system_clock::time_point _endFrameCounter = std::chrono::system_clock::now();
        // Get the frame duration
        std::chrono::duration<double, std::milli> timeElapsed = _endFrameCounter - _startFrameCounter;

        // Get the delta time as ms for the frame duration
        std::chrono::duration<double, std::milli> deltaMs(float(1000 / _frameRateCap) - timeElapsed.count());
        auto deltaMsDuration = std::chrono::duration_cast<std::chrono::milliseconds>(deltaMs);

        // Set an adjuster value if the delay is too short/long
        if (GetFPS() > _frameRateCap + 5)
            _adjuster = 1;
        else if (GetFPS() < _frameRateCap - 5)
            _adjuster = -1;

        // If the frame duration is too low and the frame rate cap is enable, slow down the frame duration
        if (timeElapsed.count() < 1000 / _frameRateCap && _frameRateCapEnabled)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(deltaMsDuration.count() + _adjuster));
        }

        // Get the sleep time and the new frame duration after the delay
        std::chrono::system_clock::time_point _endSleepCounter = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> timeSlept = _endSleepCounter - _endFrameCounter;

        // Set the complete delta time and update the FPS
        _deltaTime = (timeElapsed + timeSlept).count();
        UpdateFPS();
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
}