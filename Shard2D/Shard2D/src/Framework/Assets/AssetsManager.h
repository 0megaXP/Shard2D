#pragma once

#include <string>
#include <memory>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

#include "CustomFont.h"

#include "../Graphic/Image.h"

#include "../Utils/CustomMap.h"

namespace Shard2D
{
	class AssetsManager
	{
	private:
		AssetsManager();
		~AssetsManager();

		friend class Managers;

		std::string assetsPrefix = "Assets/";

		std::string pngSuffix = ".png";

		std::string fontSuffix = ".ttf";
		std::vector<std::shared_ptr<CustomFont>> _fontsSaved;

		CustomMap<std::string, SDL_Texture*> _texturesSaved;


	public:
		/*
		Creates and returns an Image containing the texture created from the .png found at the path given
		*/
		Image* GetImageFromPNG(const std::string path);

		/*
		Creates and returns an Image containing the font created from the .ttf found at the path given
		*/
		TTF_Font* GetFont(const std::string path);

	private:
		CustomFont* SearchFont(std::string fontName);

	};
}