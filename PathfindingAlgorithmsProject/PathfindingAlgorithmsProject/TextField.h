#pragma once

#include <memory>
#include <string>
#include <SDL_ttf.h>

#include "GameObject.h"

class TextField : public GameObject
{
public:
	TextField(std::string fontName, int size);

protected:
	~TextField();

	std::shared_ptr<Image> _image;

public:
	std::string text = "";
	TTF_Font* font;
	SDL_Color color = SDL_Color(255,255,255);

private:
	Uint8 _size = 24;

public:
	void SetSize(int newSize);
	int Size() const;

protected:
	virtual Image* GetRenderingImage() override;
};
