#include "AssetsManager.h"

#include <iostream>

AssetsManager::AssetsManager()
{
}

AssetsManager::~AssetsManager()
{
}

Image* AssetsManager::GetImagePNG(const char path[])
{
	std::cout << path << std::endl;
	SDL_Surface* newSurface = IMG_Load(path);
	Image* newImage = new Image(newSurface);
	return newImage;
}
