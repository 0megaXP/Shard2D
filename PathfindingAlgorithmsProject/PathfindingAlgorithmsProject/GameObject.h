#pragma once

#include <string>

class GraphicManager;

class GameObject
{
public:
	GameObject();

private:
	~GameObject();

	friend class GraphicManager;

protected:
	std::string _name = "";
	GameObject* _parent = nullptr;

	bool _visible = true;

public:
	std::string Name() const;
	GameObject* Parent() const;

	short x = 0;
	short y = 0;

	short GlobalX() const;
	short GlobalY() const;

	short scaleX = 1;
	short scaleY = 1;

	bool IsVisible() const;
	void SetVisibility(bool isVisible);
};

