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

#include "TextField.h"

#include "../Management/Managers.h"
#include "../ShardUtils.h"

namespace Shard2D
{
    TextField::TextField(const std::string &newText, const std::string &fontPath, int newSize)
        : _text(newText), size(newSize)
    {
        width = 1280;
        font = ShardAssets->GetFont(fontPath);

        LoadTexture();

        height = _image.get()->GetHeight();
    }

    TextField::~TextField()
    {
    }

    float TextField::AdaptedGlobalScaleX() const
    {
        if (Parent() != nullptr)
            return scaleX * NormalizedSize() * Parent()->AdaptedGlobalScaleX();
        else
            return scaleX * NormalizedSize();
    }

    float TextField::AdaptedGlobalScaleY() const
    {
        if (Parent() != nullptr)
            return scaleY * NormalizedSize() * Parent()->AdaptedGlobalScaleY();
        else
            return scaleY * NormalizedSize();
    }

    void TextField::SetText(const std::string &newText)
    {
        _text = newText;
        LoadTexture();
    }

    void TextField::SetColor(SDL_Color newColor)
    {
        color = newColor;
        LoadTexture();
    }

    float TextField::NormalizedSize() const
    {
        return ((float)size / 72);
    }

    void TextField::LoadTexture()
    {
        if (_text == "")
            _text = " ";

        SDL_Surface* textSurface;
        textSurface = TTF_RenderText_Blended_Wrapped(font, _text.c_str(), color, Uint32(width / ((scaleX + scaleY) / 2) / NormalizedSize()));
        if (!textSurface)
        {
            Log("Failed to render text: " + *TTF_GetError(), TextColor::Red);
            _image = std::shared_ptr<Image>(new Image(nullptr));
            SDL_FreeSurface(textSurface);
        }
        else
        {
            _image.reset();
            SDL_Texture* textTexture = ShardGraphic->CreateTexture(textSurface);
            SDL_FreeSurface(textSurface);
            _image = std::shared_ptr<Image>(new Image(textTexture));
        }
    }

    Image* TextField::GetRenderingImage()
    {
        return _image.get();
    }
}