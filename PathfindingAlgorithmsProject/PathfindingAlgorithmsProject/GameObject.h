#pragma once

#include <string>
#include <vector>
#include "Image.h"

class GraphicManager;

class GameObject
{
public:
	GameObject();

protected:
	virtual ~GameObject();

	friend class GraphicManager;

	std::string _name = "";
	GameObject* _parent = nullptr;
	std::vector<GameObject*> _children;

	bool _visible = true;

public:
	std::string Name() const;
	GameObject* Parent() const;

	short x = 0;
	short y = 0;

	short a = 1;

	short scaleX = 1;
	short scaleY = 1;

public:
	short GlobalX() const;
	short GlobalY() const;

	short GlobalA() const;

	short GlobalScaleX() const;
	short GlobalScaleY() const;

	bool IsVisible() const;
	void SetVisibility(bool isVisible);

	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	void RemoveChildren();

protected:
	virtual Image* GetRenderingImage();
};

