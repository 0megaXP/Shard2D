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
		TextField(const std::string &newText, const std::string &fontPath, int size);

	protected:
		~TextField();

	public:
		TTF_Font* font;
		Uint8 size = 24;

	private:
		std::string _text = "";

	protected:
		float AdaptedGlobalScaleX() const override;
		float AdaptedGlobalScaleY() const override;

	public:
		void SetText(std::string newText);
		void SetColor(SDL_Color newColor);

	private:
		float NormalizedSize() const;

		void LoadTexture();

	protected:
		virtual Image* GetRenderingImage() override;
	};
}