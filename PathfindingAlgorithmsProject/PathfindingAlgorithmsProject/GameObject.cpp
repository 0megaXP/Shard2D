#include "GameObject.h"
#include "ClockManager.h"
#include "GraphicManager.h"
#include "Managers.h"

#include <iostream>

GameObject::GameObject()
{
	_name = "New Object";
	_parent = nullptr;
	_children = std::vector<GameObject*>();

	Managers::graphicManager->ChildRemoved(this);
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

/**
Return the GambeObject's x position on the screen (counting all the parents' x)
*/
short GameObject::GlobalX() const
{
	if (_parent != nullptr)
		return x + _parent->GlobalX();
	else
		return x;
}

/**
Return the GambeObject's y position on the screen (counting all the parents' y)
*/
short GameObject::GlobalY() const
{
	if (_parent != nullptr)
		return y + _parent->GlobalY();
	else
		return y;
}

/**
Return the GambeObject's alpha (counting all the parents' alphas)
*/
short GameObject::GlobalA() const
{
	if (a <= 0 || _parent == nullptr)
		return a;
	else
		return a * _parent->GlobalA();
}


/**
Return the GambeObject's x scale on the screen (counting all the parents' x)
*/
short GameObject::GlobalScaleX() const
{
	if (_parent != nullptr)
		return scaleX * _parent->GlobalScaleX();
	else
		return scaleX;
}

/**
Return the GambeObject's y scale on the screen (counting all the parents' y)
*/
short GameObject::GlobalScaleY() const
{
	if (_parent != nullptr)
		return scaleY * _parent->GlobalScaleY();
	else
		return scaleY;
}

/**
Return true if the GameObject has to be rendered (also takes count of scale and alpha)
*/
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

/**
Set the param GameObject as child of the actual GameObject.
*/
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
		Managers::graphicManager->ChildAdded(child);
	}
}

/**
Remove the selected child from the GameObject
*/
void GameObject::RemoveChild(GameObject* child)
{
	if (child != nullptr && _children.capacity() > 0)
	{
		int count = 0;
		for (GameObject* tempChild : _children)
		{
			if (tempChild == child)
			{
				child->_parent = nullptr;
				Managers::graphicManager->ChildRemoved(child);
				_children.erase(_children.begin() + count);
				break;
			}
			count++;
		}
	}
}
/**
Remove all the children from the GameObject
*/
void GameObject::RemoveChildren()
{
	for (int i = 0; i < _children.capacity(); i++)
	{
		_children[i]->_parent = nullptr;
		Managers::graphicManager->ChildRemoved(_children[i]);
		_children.erase(_children.begin() + i);
	}
}

/**
Function called from the GraphicManager. Return the image to render
*/
Image* GameObject::GetRenderingImage()
{
	std::cout << "GameObject Image null" << std::endl;
	return nullptr;
}
