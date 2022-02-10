#include "TextField.h"

#include "../Management/Managers.h"
#include "../Utils/ShardUtils.h"

TextField::TextField(std::string newText, std::string fontName, int newSize)
    : _text(newText), size(newSize)
{
    width = 1280;
    font = M_AssetsManager->GetFont(fontName);

    LoadTexture();

    height = _image.get()->GetHeight();
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
        _image = std::shared_ptr<TextureImage>(new TextureImage(nullptr));
        SDL_FreeSurface(textSurface);
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
