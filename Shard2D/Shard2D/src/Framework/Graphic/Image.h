#pragma once

#include <string>
#include <SDL_surface.h>
#include <SDL.h>

#include "../Utils/ShardUtils.h"

namespace Shard2D
{
	struct Image
	{
	public:
		Image() {};
		Image(SDL_Texture* newTexture)
			: _texture(newTexture) 
		{
			SDL_QueryTexture(_texture, &_format, &_access, &_width, &_height);
		};
		~Image() { SDL_DestroyTexture(_texture); };

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
}