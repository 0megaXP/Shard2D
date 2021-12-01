#include "GameObject.h"
#include "ClockManager.h"

GameObject::GameObject()
{
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
	return _visible;
}

void GameObject::SetVisibility(bool isVisible)
{
	_visible = isVisible;
}
