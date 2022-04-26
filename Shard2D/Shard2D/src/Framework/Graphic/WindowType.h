#pragma once

#include <SDL_video.h>

namespace Shard2D
{
    namespace WindowType
    {
        typedef enum
        {
            FullScreen = SDL_WINDOW_FULLSCREEN_DESKTOP,
            Borderless = SDL_WINDOW_BORDERLESS,
            Window = SDL_WINDOW_SHOWN
        } Type;
    }
}