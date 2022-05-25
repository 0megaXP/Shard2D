#include "TextField.h"

#include "../Management/Managers.h"
#include "../Utils/ShardUtils.h"

namespace Shard2D
{
    TextField::TextField(const std::string &newText, const std::string &fontPath, int newSize)
        : _text(newText), size(newSize)
    {
        width = 1280;
        font = M_AssetsManager->GetFont(fontPath);

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
            _image = std::shared_ptr<Image>(new Image(nullptr));
            SDL_FreeSurface(textSurface);
        }
        else
        {
            _image.reset();
            SDL_Texture* textTexture = M_GraphicManager->CreateTexture(textSurface);
            SDL_FreeSurface(textSurface);
            _image = std::shared_ptr<Image>(new Image(textTexture));
        }
    }

    Image* TextField::GetRenderingImage()
    {
        return _image.get();
    }
}