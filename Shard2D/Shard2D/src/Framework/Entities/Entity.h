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

#pragma once

#include <string>
#include <vector>

#include "../Graphic/Image.h"

#include "../Events/EventDispatcher.h"

namespace Shard2D
{
	class Entity : public EventDispatcher
	{
	public:
		Entity();
		virtual ~Entity();

		friend class GraphicManager;
		friend class EntitiesManager;
		friend class GameManager;
		friend class EventsManager;
		friend class EntityDataParser;

		friend class TextField;

	private:
		std::string _name = "";
		Entity* _parent = nullptr;
		std::vector<Entity*> _children;

		SDL_Color _color = SDL_Color(255, 255, 255);

		bool _visible = true;
		bool _active = true;

		short _parentFixedX = 0;
		short _parentFixedY = 0;

		short _pivotOffsetX = 0;
		short _pivotOffsetY = 0;

		bool mouseOverlapped = false;

		short _finalFixedX = 0;
		short _finalFixedY = 0;

		short _finalFixedWidth = 0;
		short _finalFixedHeight = 0;

	protected:

	public:
		std::string Name() const;
		Entity* Parent() const;

		float x = 0;
		float y = 0;

		float width = 0;
		float height = 0;

		float rotation = 0;

		float a = 1;

		float scaleX = 1;
		float scaleY = 1;

		bool centerPivot = false;

		bool mouseEnabled = true;
		bool blockMouseEvents = true;

		bool showDebugRect = false;

	protected:
		short AdaptedGlobalX() const;

		short AdaptedGlobalY() const;

		virtual float AdaptedGlobalScaleX() const;

		virtual float AdaptedGlobalScaleY() const;

		/*
		Return the GambeObject's global x position using the parent fixed position
		*/
		short GlobalParentFixedX() const;
		/*
		Return the GambeObject's global y position using the parent fixed position
		*/
		short GlobalParentFixedY() const;

		/*
		Return the GambeObject's x offset caused by a parent scaleX
		*/
		short GlobalScaleFixedX() const;
		/*
		Return the GambeObject's y offset caused by a parent scaleY
		*/
		short GlobalScaleFixedY() const;

		/*
		Return the GambeObject's x rendering position (using all the fixed positions and offsets)
		*/
		short RenderingX() const;
		/*
		Return the GambeObject's y rendering position (using all the fixed positions and offsets)
		*/
		short RenderingY() const;

		/*
		Reset all the value used for the position fixing during the rendering
		*/
		void ResetFixedValues();

		/*
		Returne true if the object is overlapped with the mouse
		*/
		bool GetMouseOverlapped();

	public:
		/*
		Return the GambeObject's x position on the screen (counting all the parents' x)
		*/
		short GlobalX() const;
		/*
		Return the GambeObject's y position on the screen (counting all the parents' y)
		*/
		short GlobalY() const;

		/*
		Return the GambeObject's rotation (counting all the parents' rotations)
		*/
		float GlobalRotation() const;
		/*
		Return the GambeObject's alpha (counting all the parents' alphas)
		*/
		float GlobalA() const;

		/*
		Return the GambeObject's x scale on the screen (counting all the parents' x)
		*/
		float GlobalScaleX() const;
		/*
		Return the GambeObject's y scale on the screen (counting all the parents' y)
		*/
		float GlobalScaleY() const;

		/*
		Return true if the Entity has to be rendered (also takes count of scale and alpha)
		*/
		bool IsVisible() const;
		/*
		Set if the Entity has to be rendered (also takes count of scale and alpha)
		*/
		void SetVisibility(bool isVisible);
		/*
		Get the color of the entitiy (the alpha of the color is ignored)
		*/
		virtual SDL_Color GetColor();
		/*
		Set the color of the entitiy (the alpha of the color is ignored)
		*/
		virtual void SetColor(SDL_Color newColor);

		/*
		Return true if the Entity has run events and updates
		*/
		bool IsActive() const;
		/*
		Set if the Entity has to run events and updates
		*/
		void SetActive(bool isActive);

		/*
		Set the param Entity as child of the actual Entity.
		*/
		void AddChild(Entity* child);
		/*
		Set the param Entity as child of the actual Entity at a specific position (if position < 0 
		the position will be 0, if position > children number the position will be the last index).
		*/
		void AddChildAt(Entity* child, int position);
		/*
		Remove the selected child from the Entity
		*/
		void RemoveChild(Entity* child);
		/*
		Remove all the children from the Entity
		*/
		void RemoveChildren();

	protected:
		/*
		Function called from the GraphicManager. Return the image to render
		*/
		virtual Image* GetRenderingImage();

		std::shared_ptr<Image> _image;

		/*
		Function called when the Entity is initialized
		*/
		virtual void Init() {};

		/*
		Function called each frame
		*/
		virtual void Update() {};
	};
}