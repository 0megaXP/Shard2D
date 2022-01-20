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

TTF_Font* AssetsManager::GetFont(const std::string path)
{
	CustomFont* newFont = SearchFont(path);

	if (newFont == nullptr)
	{
		newFont = new CustomFont(path, TTF_OpenFont((assetsPrefix + fontPrefix + path + fontSuffix).c_str(), 72));
		_fontsSaved.push_back(std::shared_ptr<CustomFont>(newFont));
	}

	return newFont->font;

	//return TTF_OpenFont((assetsPrefix + fontPrefix + path + fontSuffix).c_str(), 72);
}

CustomFont* AssetsManager::SearchFont(std::string fontName)
{
	for (int i = 0; i < _fontsSaved.size(); i++)
	{
		if (_fontsSaved[i].get()->fontName == fontName)
			return _fontsSaved[i].get();
	}

	return nullptr;
}
