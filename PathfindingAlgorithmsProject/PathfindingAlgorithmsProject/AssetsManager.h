#pragma once

#include <string>
#include <SDL_image.h>
#include "Image.h"

class AssetsManager
{
public: 
	AssetsManager();
	~AssetsManager();

public:
	Image* GetImagePNG(const char path[]);
};

