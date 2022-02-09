#include "AssetsManager.h"

#include "../Utils//CustomIOStream.h"

#include "../Management/Managers.h"

AssetsManager::AssetsManager()
{
}

AssetsManager::~AssetsManager()
{
	std::vector<SDL_Texture*> textures = _texturesSaved.GetAllValues();
	
	for (SDL_Texture* texture : textures)
		SDL_DestroyTexture(texture);

	Log("AssetsManager destroyed!", TextColor::Purple);
}

SurfaceImage* AssetsManager::GetSurfaceImagePNG(const std::string path)
{
	SDL_Surface* newSurface = IMG_Load((assetsPrefix + pngPrefix + path + pngSuffix).c_str());
	SurfaceImage* newImage = new SurfaceImage(newSurface);
	return newImage;
}

TextureImage* AssetsManager::GetTextureImagePNG(const std::string path)
{
	if (_texturesSaved.Contains(path))
		return new TextureImage(_texturesSaved.Get(path));

	SDL_Surface* newSurface = IMG_Load((assetsPrefix + pngPrefix + path + pngSuffix).c_str());
	SDL_Texture* newTexture = M_GraphicManager->CreateTexture(newSurface);
	_texturesSaved.Insert(path, newTexture);
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
	for (Uint8 i = 0; i < _fontsSaved.size(); i++)
	{
		if (_fontsSaved[i].get()->fontName == fontName)
			return _fontsSaved[i].get();
	}

	return nullptr;
}