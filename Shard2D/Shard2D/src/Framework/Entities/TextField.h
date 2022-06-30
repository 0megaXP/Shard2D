/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
		void SetText(const std::string &newText);
		void SetColor(SDL_Color newColor) override;

	private:
		float NormalizedSize() const;

		void LoadTexture();

	protected:
		virtual Image* GetRenderingImage() override;
	};
}