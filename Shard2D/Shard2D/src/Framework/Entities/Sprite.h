#pragma once

#include <memory>

#include "Entity.h"

namespace Shard2D
{
	class Sprite : public Entity
	{
	public:
		Sprite();
		Sprite(Image* newImage);

	protected:
		~Sprite();

	public:
		void SetNewImage(Image* newImage, bool resetProportions);

	protected:
		virtual Image* GetRenderingImage() override;

	};
}