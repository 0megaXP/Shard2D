#pragma once

#include <memory>

#include "GameObject.h"

class Sprite : public GameObject
{
public:
	Sprite();
	Sprite(Image* newImage);

protected:
	~Sprite();

	std::shared_ptr<Image> _image;

public:

protected:
	virtual Image* GetRenderingImage() override;

};

