#include "GameObject.h"
#include "ClockManager.h"
#include "GraphicManager.h"
#include "GameObjectsManager.h"
#include "Managers.h"

#include <iostream>

import MathUtils;
GameObject::GameObject()
	: _name("New Object")//, _parent(nullptr), _children(std::vector<GameObject*>())
{
	M_GameObjectsManager->ObjectCreated(this);


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

/*
Return the GambeObject's x position on the screen (counting all the parents' x)
*/
short GameObject::GlobalX() const
{
	if (_parent != nullptr)
		return x + _parent->GlobalX();
	else
		return x;
}

/*
Return the GambeObject's y position on the screen (counting all the parents' y)
*/
short GameObject::GlobalY() const
{
	if (_parent != nullptr)
		return y + _parent->GlobalY();
	else
		return y;
}

/*
Return the GambeObject's rotation (counting all the parents' rotations)
*/
short GameObject::GlobalRotation() const
{
	if (_parent == nullptr)
		return rotation % 360;
	else
		return (_parent->GlobalRotation() + rotation) % 360;
}

/*
Return the GambeObject's alpha (counting all the parents' alphas)
*/
float GameObject::GlobalA() const
{
	if (a <= 0 || _parent == nullptr)
		return Clamp01(a);
	else
		return Clamp01(a * _parent->GlobalA());
}


/*
Return the GambeObject's x scale on the screen (counting all the parents' x)
*/
float GameObject::GlobalScaleX() const
{
	if (_parent != nullptr)
		return scaleX * _parent->GlobalScaleX();
	else
		return scaleX;
}

/*
Return the GambeObject's y scale on the screen (counting all the parents' y)
*/
float GameObject::GlobalScaleY() const
{
	if (_parent != nullptr)
		return scaleY * _parent->GlobalScaleY();
	else
		return scaleY;
}

/*
Return true if the GameObject has to be rendered (also takes count of scale and alpha)
*/
bool GameObject::IsVisible() const
{
	if (_parent != nullptr && a > 0 && scaleX != 0 && scaleY != 0)
		return _parent->IsVisible();
	else if (a > 0 && scaleX != 0 && scaleY != 0)
		return _visible;
	else
		return false;
}

/*
Set if the GameObject has to be rendered (also takes count of scale and alpha)
*/
void GameObject::SetVisibility(bool isVisible)
{
	_visible = isVisible;
}

/*
Return true if the GameObject has run events and updates
*/
bool GameObject::IsActive() const
{
	if (_parent != nullptr)
		return _parent->IsActive();
	else
		return _active;
}

/*
Set if the GameObject has to run events and updates
*/
void GameObject::SetActive(bool isActive)
{
	_active = isActive;
}

/*
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
	}
}

/*
Remove the selected child from the GameObject
*/
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

/*
Remove all the children from the GameObject
*/
void GameObject::RemoveChildren()
{
	for (int i = 0; i < _children.size(); i++)
	{
		_children[i]->_parent = nullptr;
		_children.erase(_children.begin() + i);
	}
}

/*
Function called from the GraphicManager. Return the image to render
*/
Image* GameObject::GetRenderingImage()
{
	std::cout << "GameObject Image null" << std::endl;
	return nullptr;
}

void GameObject::Init()
{
}

void GameObject::Start()
{
}

void GameObject::Update()
{
}
