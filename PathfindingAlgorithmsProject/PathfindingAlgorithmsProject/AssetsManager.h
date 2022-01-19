#pragma once

#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Image.h"

class AssetsManager
{
public: 
	AssetsManager();
	~AssetsManager();

private:
	std::string assetsPrefix = "Assets/";

	std::string pngPrefix = "PNGs/";
	std::string pngSuffix = ".png";

	std::string fontPrefix = "Fonts/";
	std::string fontSuffix = ".ttf";

public:
	Image* GetImagePNG(const std::string path);

	TTF_Font* GetFont(const std::string path, int size);

};

