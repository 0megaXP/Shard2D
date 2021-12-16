#include "AssetsManager.h"

#include <iostream>

AssetsManager::AssetsManager()
{
}

AssetsManager::~AssetsManager()
{
}

/**
Create an Image containing the .png found through the path given.
*/
Image* AssetsManager::GetImagePNG(const char path[])
{
	SDL_Surface* newSurface = IMG_Load(path);
	Image* newImage = new Image(newSurface);
	return newImage;
}
