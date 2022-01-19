#include "TextField.h"

#include "Managers.h"
#include "AssetsManager.h"
#include "CustomIOStream.h"

TextField::TextField(std::string fontName, int size)
{
    font = M_AssetsManager->GetFont(fontName, size);
}

TextField::~TextField()
{
}

void TextField::SetSize(int newSize)
{
    if (newSize < 0)
        _size = 0;
    else
        _size = newSize;
}

int TextField::Size() const
{
    return _size;
}

Image* TextField::GetRenderingImage()
{
    //if (_image.get() != nullptr)
        //delete _image.get();

    SDL_Surface* textSurface;

    textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface)
    {
        Log("Failed to render text: " + *TTF_GetError(), TextColor::Red);
        return nullptr;
    }
    _image = std::shared_ptr<Image>(new Image(textSurface));
    return _image.get();
}
