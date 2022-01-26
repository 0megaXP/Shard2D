#include "AssetsManager.h"

#include "Managers.h"
#include "GraphicManager.h"
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
SurfaceImage* AssetsManager::GetSurfaceImagePNG(const std::string path)
{
	SDL_Surface* newSurface = IMG_Load((assetsPrefix + pngPrefix + path + pngSuffix).c_str());
	SurfaceImage* newImage = new SurfaceImage(newSurface);
	return newImage;
}

TextureImage* AssetsManager::GetTextureImagePNG(const std::string path)
{
	SDL_Surface* newSurface = IMG_Load((assetsPrefix + pngPrefix + path + pngSuffix).c_str());
	SDL_Texture* newTexture = M_GraphicManager->CreateTexture(newSurface);
	TextureImage * newImage = new TextureImage(newTexture);
	SDL_FreeSurface(newSurface);
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
