#include "Entity.h"

#include <iostream>

#include "../Graphic/Image.h"
#include "../Management/Managers.h"

import MathUtils;

namespace Shard2D
{
	Entity::Entity()
		: _name("New Entity")
	{
		M_EntitiesManager->EntityCreated(this);

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

	short Entity::GlobalSelfFixedX() const
	{
		if (_parent == nullptr)
			return _selfFixedX;
		else
			return _parent->GlobalSelfFixedX() + _selfFixedX;
	}

	short Entity::GlobalSelfFixedY() const
	{
		if (_parent == nullptr)
			return _selfFixedY;
		else
			return _parent->GlobalSelfFixedY() + _selfFixedY;
	}

	short Entity::GlobalPivotOffsetX() const
	{
		return GlobalX() + _pivotOffsetX;
	}

	short Entity::GlobalPivotOffsetY() const
	{
		return GlobalY() + _pivotOffsetY;
	}

	short Entity::RenderingX() const
	{
		return GlobalX() + GlobalParentFixedX() + GlobalSelfFixedX() + _pivotOffsetX;
	}

	short Entity::RenderingY() const
	{
		return GlobalY() + GlobalParentFixedY() + GlobalSelfFixedY() + _pivotOffsetY;
	}

	void Entity::ResetFixedValues()
	{
		_parentFixedX = 0;
		_parentFixedY = 0;
		_selfFixedX = 0;
		_selfFixedY = 0;
		_pivotOffsetX = 0;
		_pivotOffsetY = 0;
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

	short Entity::PivotX() const
	{
		return short(x - _pivotOffsetX);
	}

	short Entity::PivotY() const
	{
		return short(y - _pivotOffsetY);
	}

	short Entity::GlobalPivotX() const
	{
		return GlobalX() - _pivotOffsetX;
	}

	short Entity::GlobalPivotY() const
	{
		return GlobalY() - _pivotOffsetY;
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
			return Clamp01(a);
		else
			return Clamp01(a * _parent->GlobalA());
	}

	float Entity::GlobalScaleX() const
	{
		float widthScale = 1;
		if (_image != nullptr)
			widthScale = width / _image.get()->GetWidth();

		if (_parent != nullptr)
			return scaleX * _parent->GlobalScaleX() * widthScale;
		else
			return scaleX * widthScale;
	}

	float Entity::GlobalScaleY() const
	{
		float heightScale = 1;
		if (_image != nullptr)
			heightScale = height / _image.get()->GetHeight();

		if (_parent != nullptr)
			return scaleY * _parent->GlobalScaleY() * heightScale;
		else
			return scaleY * heightScale;
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