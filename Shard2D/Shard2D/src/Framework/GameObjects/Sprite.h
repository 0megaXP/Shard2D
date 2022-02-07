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

public:

protected:
	virtual Image* GetRenderingImage() override;

};

