#pragma once

#define SURFACE_TYPE "Surface"
#define TEXTURE_TYPE "Texture"

#include <string>
#include <SDL_surface.h>
#include <SDL.h>

#include "../Utils/ShardUtils.h"

struct Image
{
public:
	Image() {};
	~Image() {};

	std::string type;

	virtual float GetWidth() { return 0; };

	virtual float GetHeight() { return 0; };

private:
	friend class GraphicManager;
};

struct SurfaceImage : Image
{
public:
	SurfaceImage()
	{
		type = SURFACE_TYPE;
	};

	SurfaceImage(SDL_Surface* newSurface)
		: _surface(newSurface)
	{
		type = SURFACE_TYPE;
	};

	~SurfaceImage() { SDL_FreeSurface(_surface); };

private:
	SDL_Surface* _surface;

	friend class GraphicManager;
};

struct TextureImage : Image
{
public:
	TextureImage()
	{
		type = TEXTURE_TYPE;
	};

	TextureImage(SDL_Texture* newTexture)
		: _texture(newTexture)
	{
		type = TEXTURE_TYPE;
		SDL_QueryTexture(_texture, &_format, &_access, &_width, &_height);
	};

	~TextureImage() { SDL_DestroyTexture(_texture); };

	float GetWidth() { return float(_width); };

	float GetHeight() { return float(_height); };

private:
	SDL_Texture* _texture;

	int _width;
	int _height;
	int _access;
	unsigned int _format;

	friend class GraphicManager;
};

