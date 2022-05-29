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

		SDL_Surface* newSurface = IMG_Load((path).c_str());
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
			newFont = new CustomFont(path, TTF_OpenFont((path).c_str(), 72));
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