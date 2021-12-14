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
	friend class GameObjectsManager;
	friend class GameManager;

	std::string _name = "";
	GameObject* _parent = nullptr;
	std::vector<GameObject*> _children;

	bool _visible = true;

public:
	std::string Name() const;
	GameObject* Parent() const;

	short x = 0;
	short y = 0;

	float a = 1;

	float scaleX = 1;
	float scaleY = 1;

public:
	short GlobalX() const;
	short GlobalY() const;

	float GlobalA() const;

	float GlobalScaleX() const;
	float GlobalScaleY() const;

	bool IsVisible() const;
	void SetVisibility(bool isVisible);

	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	void RemoveChildren();

protected:
	virtual Image* GetRenderingImage();

	virtual void Init();

	virtual void Start();

	virtual void Update();
};

