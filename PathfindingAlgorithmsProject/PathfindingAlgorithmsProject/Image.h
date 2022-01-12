#pragma once

#include <string>
#include <SDL_surface.h>

struct Image
{
public:
	Image(SDL_Surface* newSurface)
		: _surface(newSurface), _rotatedSurface(nullptr)
	{ };

	~Image() { SDL_FreeSurface(_surface); SDL_FreeSurface(_rotatedSurface); };

private:
	SDL_Surface* _surface;
	SDL_Surface* _rotatedSurface;

	friend class GraphicManager;
};

