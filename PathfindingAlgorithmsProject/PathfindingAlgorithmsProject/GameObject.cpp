#include "GameObject.h"
#include "ClockManager.h"
#include "GraphicManager.h"

GameObject::GameObject()
{
	_parent = nullptr;
	_children = std::vector<GameObject*>();
}

GameObject::~GameObject()
{
}

std::string GameObject::Name() const
{
	return _name;
}

GameObject* GameObject::Parent() const
{
	return _parent;
}

short GameObject::GlobalX() const
{
	if (_parent != nullptr)
		return x + _parent->GlobalX();
	else
		return x;
}

short GameObject::GlobalY() const
{
	if (_parent != nullptr)
		return y + _parent->GlobalY();
	else
		return y;
}

short GameObject::GlobalA() const
{
	if (a <= 0 || _parent == nullptr)
		return a;
	else
		return a * _parent->GlobalA();
}

short GameObject::GlobalScaleX() const
{
	if (_parent != nullptr)
		return scaleX * _parent->GlobalScaleX();
	else
		return scaleX;
}

short GameObject::GlobalScaleY() const
{
	if (_parent != nullptr)
		return scaleY * _parent->GlobalScaleY();
	else
		return scaleY;
}

bool GameObject::IsVisible() const
{
	if (_parent != nullptr)
		return _parent->IsVisible();
	else if (a > 0)
		return _visible;
	else
		return false;
}

void GameObject::SetVisibility(bool isVisible)
{
	_visible = isVisible;
}

void GameObject::AddChild(GameObject* child)
{
	if (child != nullptr)
	{
		_children.push_back(child);
		child->_parent = this;
		
		// GraphicManager functions
	}
}

void GameObject::RemoveChild(GameObject* child)
{
	if (child != nullptr && _children.capacity() > 0)
	{
		int count = 0;
		for (GameObject* tempChild : _children)
		{
			if (tempChild == child)
			{
				_children.erase(_children.begin() + count);
				child->_parent = nullptr;
				break;
			}
			count++;
		}

		// GraphicManager functions
	}
}

void GameObject::RemoveChildren()
{
	for (int i = 0; i < _children.capacity(); i++)
	{
		_children.erase(_children.begin() + i);
		_children[i]->_parent = nullptr;

		// GraphicManager functions
	}
}

void GameObject::RenderObject()
{
	// Overridable function
}
