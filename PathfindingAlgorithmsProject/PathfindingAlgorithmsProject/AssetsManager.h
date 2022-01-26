#pragma once

#include <string>
#include <memory>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Image.h"
#include "CustomFont.h"
#include <vector>
#include "CustomMap.h"

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

	CustomMap<std::string, SDL_Texture*> _texturesSaved;


public:
	/**
	Creates and returns an Image containing the surface created from the .png found at the path given
	*/
	SurfaceImage* GetSurfaceImagePNG(const std::string path);

	/*
	Creates and returns an Image containing the texture created from the .png found at the path given
	*/
	TextureImage* GetTextureImagePNG(const std::string path);

	/*
	Creates and returns an Image containing the font created from the .ttf found at the path given
	*/
	TTF_Font* GetFont(const std::string path);

private:
	CustomFont* SearchFont(std::string fontName);

};

