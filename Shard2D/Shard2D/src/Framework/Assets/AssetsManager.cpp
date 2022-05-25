#include "AssetsManager.h"

#include "../Utils//CustomIOStream.h"

#include "../Management/Managers.h"

namespace Shard2D
{
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

	Image* AssetsManager::GetImageFromPNG(const std::string &path)
	{
		if (_texturesSaved.Contains(path))
			return new Image(_texturesSaved.Get(path));

		SDL_Surface* newSurface = IMG_Load((assetsPrefix + path + pngSuffix).c_str());
		SDL_Texture* newTexture = M_GraphicManager->CreateTexture(newSurface);
		_texturesSaved.Insert(path, newTexture);
		Image* newImage = new Image(newTexture);
		SDL_FreeSurface(newSurface);
		return newImage;
	}

	TTF_Font* AssetsManager::GetFont(const std::string &path)
	{
		CustomFont* newFont = SearchFont(path);

		if (newFont == nullptr)
		{
			newFont = new CustomFont(path, TTF_OpenFont((assetsPrefix + path + fontSuffix).c_str(), 72));
			_fontsSaved.push_back(std::shared_ptr<CustomFont>(newFont));
			Log("New font created", TextColor::Aqua);
		}

		return newFont->font;
	}

	CustomFont* AssetsManager::SearchFont(const std::string &fontName)
	{
		for (Uint8 i = 0; i < _fontsSaved.size(); i++)
		{
			if (_fontsSaved[i].get()->fontName == fontName)
				return _fontsSaved[i].get();
		}

		return nullptr;
	}
}