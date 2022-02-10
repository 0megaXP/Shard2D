#include "Sprite.h"

#include "../Utils/ShardUtils.h"

Sprite::Sprite()
{
	std::cout << "Sprite object created! -> ";
}

Sprite::Sprite(Image* newImage)
{
	this->_image = std::shared_ptr<Image>(newImage);

	width = _image->GetWidth();
	height = _image->GetHeight();

	std::cout << "Sprite object created! -> ";
}

Sprite::~Sprite()
{
	std::cout << "Sprite object destroyed! -> ";
}

void Sprite::SetNewImage(Image* newImage, bool resetProportions = true)
{
	this->_image = std::shared_ptr<Image>(newImage);

	if (resetProportions)
	{
		width = _image->GetWidth();
		height = _image->GetHeight();
	}
}

Image* Sprite::GetRenderingImage()
{
	return _image.get();
}