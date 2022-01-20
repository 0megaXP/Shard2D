#pragma once

#include <memory>
#include <string>
#include <SDL_ttf.h>

#include "GameObject.h"

class TextField : public GameObject
{
public:
	TextField(std::string newText, std::string fontName, int size);

protected:
	~TextField();

	std::shared_ptr<Image> _image;

public:
	TTF_Font* font;
	Uint32 width = 1280;
	Uint8 size = 24;

private:
	std::string _text = "";
	SDL_Color _color = SDL_Color(255,255,255);

public:
	float GlobalScaleX() const override;
	float GlobalScaleY() const override;

	void SetText(std::string newText);
	void SetColor(SDL_Color newColor);

private:
	float NormalizedSize() const;

	void UpdateSurface();

protected:
	virtual Image* GetRenderingImage() override;
};
