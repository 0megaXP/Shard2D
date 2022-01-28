#include "TextField.h"

#include "../Management/Managers.h"
#include "../Utils/ShardUtils.h"

TextField::TextField(std::string newText, std::string fontName, int newSize)
    : _text(newText), size(newSize)
{
    font = M_AssetsManager->GetFont(fontName);

    SDL_Surface* textSurface;

    textSurface = TTF_RenderText_Blended_Wrapped(font, _text.c_str(), _color, width / ((scaleX + scaleY) / 2) / NormalizedSize());
    if (!textSurface)
    {
        Log("Failed to render text", TextColor::Red);
        _image = std::shared_ptr<TextureImage>(new TextureImage(nullptr));
    }
    else
    {
        SDL_Texture* textTexture = M_GraphicManager->CreateTexture(textSurface);
        SDL_FreeSurface(textSurface);
        _image = std::shared_ptr<TextureImage>(new TextureImage(textTexture));
    }
}

TextField::~TextField()
{
}

float TextField::GlobalScaleX() const
{
    if (Parent() != nullptr)
        return scaleX * ((float)size / 72) * Parent()->GlobalScaleX();
    else
        return scaleX * ((float)size / 72);
}

float TextField::GlobalScaleY() const
{
    if (Parent() != nullptr)
        return scaleY * NormalizedSize() * Parent()->GlobalScaleY();
    else
        return scaleY * NormalizedSize();
}

void TextField::SetText(std::string newText)
{
    _text = newText;
    UpdateSurface();
}

void TextField::SetColor(SDL_Color newColor)
{
    _color = newColor;
    UpdateSurface();
}

float TextField::NormalizedSize() const
{
    return ((float)size / 72);
}

void TextField::UpdateSurface()
{
    SDL_Surface* textSurface;

    textSurface = TTF_RenderText_Blended_Wrapped(font, _text.c_str(), _color, width / ((scaleX + scaleY) / 2) / NormalizedSize());
    if (!textSurface)
    {
        Log("Failed to render text: " + *TTF_GetError(), TextColor::Red);
        _image = std::shared_ptr<TextureImage>(new TextureImage(nullptr));
    }
    else
    {
        _image.reset();
        SDL_Texture* textTexture = M_GraphicManager->CreateTexture(textSurface);
        SDL_FreeSurface(textSurface);
        _image = std::shared_ptr<TextureImage>(new TextureImage(textTexture));
    }
}

Image* TextField::GetRenderingImage()
{
    return _image.get();
}
