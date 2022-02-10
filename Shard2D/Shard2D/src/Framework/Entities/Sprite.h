#pragma once

#include <memory>

#include "Entity.h"

class Sprite : public Entity
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

