#pragma once

#include <memory>
#include <string>
#include <SDL_ttf.h>

#include "Entity.h"

namespace Shard2D
{
	class TextField : public Entity
	{
	public:
		TextField(std::string newText, std::string fontName, int size);

	protected:
		~TextField();

	public:
		TTF_Font* font;
		Uint8 size = 24;

	private:
		std::string _text = "";

	public:
		float GlobalScaleX() const override;
		float GlobalScaleY() const override;

		void SetText(std::string newText);
		void SetColor(SDL_Color newColor);

	private:
		float NormalizedSize() const;

		void LoadTexture();

	protected:
		virtual Image* GetRenderingImage() override;
	};
}