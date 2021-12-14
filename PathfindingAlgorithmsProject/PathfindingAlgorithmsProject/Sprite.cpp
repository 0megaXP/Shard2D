#include "Sprite.h"

#include <iostream>


Sprite::Sprite()
{
	_image = nullptr;
}

Sprite::Sprite(Image* newImage)
{
	_image = newImage;
}

Sprite::~Sprite()
{
	if (_image != nullptr)
		delete(_image);
}

Image* Sprite::GetRenderingImage()
{
	std::cout << "Sprite Image returned" << std::endl;
	return _image;
}