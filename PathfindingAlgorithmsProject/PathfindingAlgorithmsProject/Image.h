#pragma once

#define SURFACE_TYPE "Surface"
#define TEXTURE_TYPE "Texture"

#include <string>
#include <SDL_surface.h>
#include <SDL.h>

struct Image
{
public:
	Image() {};
	~Image() {};

	std::string type;

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
	};

	~TextureImage() { SDL_DestroyTexture(_texture); };

private:
	SDL_Texture* _texture;

	friend class GraphicManager;
};

