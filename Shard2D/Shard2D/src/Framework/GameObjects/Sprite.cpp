#include "Sprite.h"

#include "../Utils/ShardUtils.h"

Sprite::Sprite()
{
	std::cout << "Sprite object created! -> ";
}

Sprite::Sprite(Image* newImage)
	: _image(std::shared_ptr<Image>(newImage))
{
	std::cout << "Sprite object created! -> ";
}

Sprite::~Sprite()
{
	std::cout << "Sprite object destroyed! -> ";
}

Image* Sprite::GetRenderingImage()
{

	return _image.get();
}