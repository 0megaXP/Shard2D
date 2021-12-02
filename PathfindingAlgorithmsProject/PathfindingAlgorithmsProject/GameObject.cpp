#include "GameObject.h"
#include "ClockManager.h"

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

bool GameObject::IsVisible() const
{
	if (_parent != nullptr)
		return _parent->IsVisible();
	else
		return _visible;

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
	if (child != nullptr)
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
}
