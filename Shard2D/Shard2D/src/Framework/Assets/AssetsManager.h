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
		Image* GetImageFromPNG(const std::string &path);

		/*
		Creates and returns an Image containing the font created from the .ttf found at the path given
		*/
		TTF_Font* GetFont(const std::string &path);

	private:
		CustomFont* SearchFont(const std::string &fontName);

	};
}