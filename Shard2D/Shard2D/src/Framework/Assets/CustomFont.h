#pragma once

#include <memory>
#include <string>
#include <SDL_ttf.h>

#include "../Utils/ShardUtils.h"

struct CustomFont
{
	CustomFont(std::string newName, TTF_Font* newFont)
		: fontName(newName), font(newFont)
	{};

	~CustomFont() 
	{
		Log(fontName + " font deleted succesfully!", TextColor::Purple);
		TTF_CloseFont(font);
	};

	std::string fontName;
	TTF_Font* font;
};

