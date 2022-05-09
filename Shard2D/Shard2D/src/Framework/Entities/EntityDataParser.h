#pragma once

#include <SDL.h>

namespace Shard2D
{
	class Entity;
	class Image;
	struct Vector2;

	class EntityDataParser
	{
	public:
		static SDL_Rect GetRenderingRect(Entity* entity, Image* image);

		static SDL_Point GetRotationPoint(Entity* entity, Image* image);

		static Uint8 GetRenderingAlpha(Entity* entity);

		static Vector2 GetPositionOffsetForParentRotation(Entity* _entity);

		static int GetPivotOffsetX(Entity* entity, Image* image);

		static int GetPivotOffsetY(Entity* entity, Image* image);

	};
}

