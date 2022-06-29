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

#include "Entity.h"

#include <iostream>

#include "../Graphic/Image.h"
#include "../Management/Managers.h"

#include "../ShardUtils.h"

//import MathUtils;

namespace Shard2D
{
	Entity::Entity()
		: _name("New Entity")
	{
		ShardEntities->EntityCreated(this);

		Init();

		std::cout << "Entity created!" << std::endl;
	}

	Entity::~Entity()
	{
		std::cout << "Entity destroyed!" << std::endl;
	}

	std::string Entity::Name() const
	{
		return _name;
	}

	Entity* Entity::Parent() const
	{
		return _parent;
	}

	short Entity::AdaptedGlobalX() const
	{
		if (_parent != nullptr)
			return short(x + _parent->AdaptedGlobalX());
		else
			return short(x);
	}

	short Entity::AdaptedGlobalY() const
	{
		if (_parent != nullptr)
			return short(y + _parent->AdaptedGlobalY());
		else
			return short(y);
	}

	float Entity::AdaptedGlobalScaleX() const
	{
		float widthScale = 1;
		if (_image != nullptr)
			widthScale = width / _image.get()->GetWidth();

		if (_parent != nullptr)
			return scaleX * _parent->AdaptedGlobalScaleX() * widthScale;
		else
			return scaleX * widthScale;
	}

	float Entity::AdaptedGlobalScaleY() const
	{
		float heightScale = 1;
		if (_image != nullptr)
			heightScale = height / _image.get()->GetHeight();

		if (_parent != nullptr)
			return scaleY * _parent->AdaptedGlobalScaleY() * heightScale;
		else
			return scaleY * heightScale;
	}

	short Entity::GlobalParentFixedX() const
	{
		if (_parent == nullptr)
			return _parentFixedX;
		else
			return _parent->GlobalParentFixedX() + _parentFixedX;
	}

	short Entity::GlobalParentFixedY() const
	{
		if (_parent == nullptr)
			return _parentFixedY;
		else
			return _parent->GlobalParentFixedY() + _parentFixedY;
	}

	short Entity::GlobalScaleFixedX() const
	{
		if (_parent == nullptr)
			return 0;
		else
			return _parent->GlobalScaleFixedX() + x * (_parent->GlobalScaleX()) - x;
	}

	short Entity::GlobalScaleFixedY() const
	{
		if (_parent == nullptr)
			return 0;
		else
			return _parent->GlobalScaleFixedY() + y * (_parent->GlobalScaleY()) - y;
	}

	short Entity::RenderingX() const
	{
		return GlobalX() + GlobalParentFixedX() + _pivotOffsetX;
	}

	short Entity::RenderingY() const
	{
		return GlobalY() + GlobalParentFixedY() + _pivotOffsetY;
	}

	void Entity::ResetFixedValues()
	{
		_parentFixedX = 0;
		_parentFixedY = 0;
		_pivotOffsetX = 0;
		_pivotOffsetY = 0;
	}

	bool Entity::GetMouseOverlapped()
	{
		return mouseOverlapped;
	}

	short Entity::GlobalX() const
	{
		if (_parent != nullptr)
			return short(x + _parent->GlobalX());
		else
			return short(x);
	}

	short Entity::GlobalY() const
	{
		if (_parent != nullptr)
			return short(y + _parent->GlobalY());
		else
			return short(y);
	}

	float Entity::GlobalRotation() const
	{
		if (_parent == nullptr)
			return rotation;// % 360;
		else
			return (_parent->GlobalRotation() + rotation);// % 360;
	}

	float Entity::GlobalA() const
	{
		if (a <= 0 || _parent == nullptr)
			return MathUtils::Clamp01(a);
		else
			return MathUtils::Clamp01(a * _parent->GlobalA());
	}

	float Entity::GlobalScaleX() const
	{
		if (_parent != nullptr)
			return scaleX * _parent->GlobalScaleX();
		else
			return scaleX;
	}

	float Entity::GlobalScaleY() const
	{
		if (_parent != nullptr)
			return scaleY * _parent->GlobalScaleY();
		else
			return scaleY;
	}

	bool Entity::IsVisible() const
	{
		if (_parent != nullptr && a > 0 && scaleX != 0 && scaleY != 0)
			return _parent->IsVisible();
		else if (a > 0 && scaleX != 0 && scaleY != 0)
			return _visible;
		else
			return false;
	}

	void Entity::SetVisibility(bool isVisible)
	{
		_visible = isVisible;
	}

	bool Entity::IsActive() const
	{
		if (_parent != nullptr)
			return _parent->IsActive();
		else
			return _active;
	}

	void Entity::SetActive(bool isActive)
	{
		_active = isActive;
	}

	void Entity::AddChild(Entity* child)
	{
		if (child != nullptr)
		{
			if (child->Parent() != nullptr)
			{
				child->Parent()->RemoveChild(child);
			}
			_children.push_back(child);
			child->_parent = this;
		}
	}

	void Entity::AddChildAt(Entity* child, int position)
	{
		if (position < 0)
			position = 0;


		if (child != nullptr)
		{
			if (child->Parent() != nullptr)
			{
				child->Parent()->RemoveChild(child);
			}
			if(position > _children.size())
				_children.push_back(child);
			else
			_children.insert(_children.begin() + position, child);
			child->_parent = this;
		}
	}

	void Entity::RemoveChild(Entity* child)
	{
		if (child != nullptr && _children.size() > 0)
		{
			int count = 0;
			for (Entity* tempChild : _children)
			{
				if (tempChild == child)
				{
					child->_parent = nullptr;
					_children.erase(_children.begin() + count);
					break;
				}
				count++;
			}
		}
	}

	void Entity::RemoveChildren()
	{
		for (Uint8 i = 0; i < _children.size(); i++)
		{
			_children[i]->_parent = nullptr;
			_children.erase(_children.begin() + i);
		}
	}

	Image* Entity::GetRenderingImage()
	{
		return nullptr;
	}
}