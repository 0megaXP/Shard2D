#include "GameObject.h"

#include <iostream>

#include "../Management/Managers.h"

import MathUtils;

GameObject::GameObject()
	: _name("New Object")
{
	M_GameObjectsManager->ObjectCreated(this);

	Init();

	std::cout << "GameObject created!" << std::endl;
}

GameObject::~GameObject()
{
	std::cout << "GameObject destroyed!" << std::endl;
}

std::string GameObject::Name() const
{
	return _name;
}

GameObject* GameObject::Parent() const
{
	return _parent;
}

short GameObject::GlobalParentFixedX() const
{
	if(_parent == nullptr)
		return _parentFixedX;
	else
		return _parent->GlobalParentFixedX() + _parentFixedX;
}

short GameObject::GlobalParentFixedY() const
{
	if (_parent == nullptr)
		return _parentFixedY;
	else
		return _parent->GlobalParentFixedY() + _parentFixedY;
}

short GameObject::GlobalSelfFixedX() const
{
	if (_parent == nullptr)
		return _selfFixedX;
	else
		return _parent->GlobalSelfFixedX() + _selfFixedX;
}

short GameObject::GlobalSelfFixedY() const
{
	if (_parent == nullptr)
		return _selfFixedY;
	else
		return _parent->GlobalSelfFixedY() + _selfFixedY;
}

short GameObject::GlobalPivotOffsetX() const
{
	return GlobalX() + _pivotOffsetX;
}

short GameObject::GlobalPivotOffsetY() const
{
	return GlobalY() + _pivotOffsetY;
}

short GameObject::RenderingX() const
{
	return GlobalX() + GlobalParentFixedX() + GlobalSelfFixedX() + _pivotOffsetX;
}

short GameObject::RenderingY() const
{
	return GlobalY() + GlobalParentFixedY() + GlobalSelfFixedY() + _pivotOffsetY;
}

void GameObject::ResetFixedValues()
{
	_parentFixedX = 0;
	_parentFixedY = 0; 
	_selfFixedX = 0; 
	_selfFixedY = 0; 
	_pivotOffsetX = 0; 
	_pivotOffsetY = 0;
}

short GameObject::GlobalX() const
{
	if (_parent != nullptr)
		return short(x + _parent->GlobalX());
	else
		return short(x);
}

short GameObject::GlobalY() const
{
	if (_parent != nullptr)
		return short(y + _parent->GlobalY());
	else
		return short(y);
}

short GameObject::PivotX() const
{
	return short(x - _pivotOffsetX);
}

short GameObject::PivotY() const
{
	return short(y - _pivotOffsetY);
}

short GameObject::GlobalPivotX() const
{
	return GlobalX() - _pivotOffsetX;
}

short GameObject::GlobalPivotY() const
{
	return GlobalY() - _pivotOffsetY;
}

float GameObject::GlobalRotation() const
{
	if (_parent == nullptr)
		return rotation;// % 360;
	else
		return (_parent->GlobalRotation() + rotation);// % 360;
}

float GameObject::GlobalA() const
{
	if (a <= 0 || _parent == nullptr)
		return Clamp01(a);
	else
		return Clamp01(a * _parent->GlobalA());
}

float GameObject::GlobalScaleX() const
{
	if (_parent != nullptr)
		return scaleX * _parent->GlobalScaleX();
	else
		return scaleX;
}

float GameObject::GlobalScaleY() const
{
	if (_parent != nullptr)
		return scaleY * _parent->GlobalScaleY();
	else
		return scaleY;
}

bool GameObject::IsVisible() const
{
	if (_parent != nullptr && a > 0 && scaleX != 0 && scaleY != 0)
		return _parent->IsVisible();
	else if (a > 0 && scaleX != 0 && scaleY != 0)
		return _visible;
	else
		return false;
}

void GameObject::SetVisibility(bool isVisible)
{
	_visible = isVisible;
}

bool GameObject::IsActive() const
{
	if (_parent != nullptr)
		return _parent->IsActive();
	else
		return _active;
}

void GameObject::SetActive(bool isActive)
{
	_active = isActive;
}

void GameObject::AddChild(GameObject* child)
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

void GameObject::RemoveChild(GameObject* child)
{
	if (child != nullptr && _children.size() > 0)
	{
		int count = 0;
		for (GameObject* tempChild : _children)
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

void GameObject::RemoveChildren()
{
	for (Uint8 i = 0; i < _children.size(); i++)
	{
		_children[i]->_parent = nullptr;
		_children.erase(_children.begin() + i);
	}
}

Image* GameObject::GetRenderingImage()
{
	return nullptr;
}
