/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "EntityDataParser.h"

#include "Entity.h"
#include "../Management/Managers.h"

#include "../Graphic/Image.h"

import MathUtils;

namespace Shard2D
{
	SDL_Rect EntityDataParser::GetRenderingRect(Entity* entity, Image* image)
	{
		SDL_Rect rect = SDL_Rect();

		// Set the offset for the entity pivot
		int pivotOffsetX = 0;
		int pivotOffsetY = 0;
		if (entity->centerPivot)
		{
			pivotOffsetX = GetPivotOffsetX(entity, image);
			pivotOffsetY = GetPivotOffsetY(entity, image);
		}

		// Apply the fix for the parent rotation
		Vector2 parentRotationFixedOffset = GetPositionOffsetForParentRotation(entity);
		entity->_parentFixedX = parentRotationFixedOffset.x;
		entity->_parentFixedY = parentRotationFixedOffset.y;

		int globalX = entity->AdaptedGlobalX();
		int globalY = entity->AdaptedGlobalY();
		
		// Set the x position where the entity need to be rendered
		int renderingX = globalX + pivotOffsetX + entity->GlobalParentFixedX();
		int renderingY = globalY + pivotOffsetY + entity->GlobalParentFixedY();

		entity->_finalFixedX = renderingX;
		entity->_finalFixedY = renderingY;

		// Set the width and the height of the rect where the entity will be printed
		float width = entity->AdaptedGlobalScaleX() * image->GetWidth();
		float height = entity->AdaptedGlobalScaleY() * image->GetHeight();

		entity->_finalFixedWidth = width;
		entity->_finalFixedHeight = height;

		// Set the rect values using the horizontal and vertical adapter
		rect.x = renderingX * M_GraphicManager->GetHorizontalResolutionAdapter();
		rect.y = renderingY * M_GraphicManager->GetVerticalResolutionAdapter();
		rect.w = width * M_GraphicManager->GetHorizontalResolutionAdapter();
		rect.h = height * M_GraphicManager->GetVerticalResolutionAdapter();

		return rect;
	}

	SDL_Point EntityDataParser::GetRotationPoint(Entity* entity, Image* image)
	{
		SDL_Point rotPoint = SDL_Point();

		rotPoint.x = 0;
		rotPoint.y = 0;
		if (entity->centerPivot)
		{
			rotPoint.x = -GetPivotOffsetX(entity, image) * M_GraphicManager->GetHorizontalResolutionAdapter();
			rotPoint.y = -GetPivotOffsetY(entity, image) * M_GraphicManager->GetVerticalResolutionAdapter();
		}

		return rotPoint;
	}

	Uint8 EntityDataParser::GetRenderingAlpha(Entity* entity)
	{
		return Uint8(entity->GlobalA() * 255);
	}

	Vector2 EntityDataParser::GetPositionOffsetForParentRotation(Entity* _entity)
	{
		// This function is used for fixing the Entity's position during its parent's rotation.
		if (_entity->Parent() != nullptr)
		{
			// Now the centre of the circumference is the parent global position
			Vector2 centre = Vector2(_entity->Parent()->AdaptedGlobalX() + _entity->Parent()->GlobalScaleFixedX(), _entity->Parent()->AdaptedGlobalY() + _entity->Parent()->GlobalScaleFixedY());
			// Here we must use the global position, because the rendering position is already affected by the selfFixed values
			float radius = Distance(Vector2(_entity->AdaptedGlobalX() + _entity->GlobalScaleFixedX(), _entity->AdaptedGlobalY() + _entity->GlobalScaleFixedY()), centre);
			if (radius > 0)
			{
				Vector2 _objectLocalPosition = Vector2(_entity->x, _entity->y);

				int _objectActualRotation = int(DegFromPosition(_objectLocalPosition, Vector2()));
				Vector2 normalizedPosition = PositionFromDeg(_entity->Parent()->GlobalRotation() + _objectActualRotation);

				int fixedX = int(normalizedPosition.x * radius - _entity->x);
				int fixedY = int(normalizedPosition.y * radius - _entity->y);
				return Vector2(fixedX, fixedY);
			}
		}

		return Vector2();
	}

	int EntityDataParser::GetPivotOffsetX(Entity* entity, Image* image)
	{
		return -image->GetWidth() / 2 * entity->AdaptedGlobalScaleX();
	}

	int EntityDataParser::GetPivotOffsetY(Entity* entity, Image* image)
	{
		return -image->GetHeight() / 2 * entity->AdaptedGlobalScaleY();
	}

}