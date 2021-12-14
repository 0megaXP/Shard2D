#pragma once

#include "GameObject.h"

class Sprite : public GameObject
{
public:
	Sprite();
	Sprite(Image* newImage);

protected:
	~Sprite();

	Image* _image;

public:

protected:
	virtual Image* GetRenderingImage() override;

};

