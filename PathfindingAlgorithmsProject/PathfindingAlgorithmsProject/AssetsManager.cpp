#include "AssetsManager.h"

#include "CustomIOStream.h"

AssetsManager::AssetsManager()
{
}

AssetsManager::~AssetsManager()
{
	Log("AssetsManager destroyed!", TextColor::Purple);
}

/**
Create an Image containing the .png found through the path given.
*/
Image* AssetsManager::GetImagePNG(const std::string path)
{
	SDL_Surface* newSurface = IMG_Load((assetsPrefix + pngPrefix + path + pngSuffix).c_str());
	Image* newImage = new Image(newSurface);
	return newImage;
}

TTF_Font* AssetsManager::GetFont(const std::string path, int size)
{
	return TTF_OpenFont((assetsPrefix + fontPrefix + path + fontSuffix).c_str(), size);
}
