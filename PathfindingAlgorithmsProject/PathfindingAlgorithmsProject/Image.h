#pragma once

#include <string>
#include <SDL_surface.h>

struct Image
{
public:
	Image(SDL_Surface* newSurface) { _surface = newSurface; };

	~Image() { SDL_FreeSurface(_surface); };

private:
	SDL_Surface* _surface;

	friend class GraphicManager;
};

