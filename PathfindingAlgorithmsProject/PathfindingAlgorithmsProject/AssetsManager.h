#pragma once

#include <string>
#include <memory>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Image.h"
#include "CustomFont.h"
#include <vector>

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
	std::vector<std::shared_ptr<CustomFont>> _fontsSaved;

public:
	SurfaceImage* GetSurfaceImagePNG(const std::string path);

	TextureImage* GetTextureImagePNG(const std::string path);

	TTF_Font* GetFont(const std::string path);

private:
	CustomFont* SearchFont(std::string fontName);

};

