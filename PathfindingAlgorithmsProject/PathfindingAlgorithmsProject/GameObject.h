#pragma once

#include <string>
#include <vector>
#include "Image.h"

class GraphicManager;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	friend class GraphicManager;
	friend class GameObjectsManager;
	friend class GameManager;

private:
	std::string _name = "";
	GameObject* _parent = nullptr;
	std::vector<GameObject*> _children;

	bool _visible = true;
	bool _active = true;

	short _parentFixedX = 0;
	short _parentFixedY = 0;

	short _selfFixedX = 0;
	short _selfFixedY = 0;

	short _pivotOffsetX = 0;
	short _pivotOffsetY = 0;

public:
	std::string Name() const;
	GameObject* Parent() const;

	short x = 0;
	short y = 0;

	short rotation = 0;

	float a = 1;

	float scaleX = 1;
	float scaleY = 1;

	bool centerPivot = false;

private:
	/*
	Return the GambeObject's global x position using the pivot offset
	*/
	short GlobalPivotOffsetX() const;
	/*
	Return the GambeObject's global y position using the pivot offset
	*/
	short GlobalPivotOffsetY() const;

	/*
	Return the GambeObject's global x position using the parent fixed position
	*/
	short GlobalParentFixedX() const;
	/*
	Return the GambeObject's global y position using the parent fixed position
	*/
	short GlobalParentFixedY() const;

	/*
	Return the GambeObject's global x position using the self fixed position
	*/
	short GlobalSelfFixedX() const;
	/*
	Return the GambeObject's global y position using the self fixed position
	*/
	short GlobalSelfFixedY() const;

	/*
	Return the GambeObject's x rendering position (using all the fixed positions and offsets)
	*/
	short RenderingX() const;
	/*
	Return the GambeObject's y rendering position (using all the fixed positions and offsets)
	*/
	short RenderingY() const;

	/*
	Reset all the value used for the position fixing during the rendering
	*/
	void ResetFixedValues();

public:
	/*
	Return the GambeObject's x position on the screen (counting all the parents' x)
	*/
	short GlobalX() const;
	/*
	Return the GambeObject's y position on the screen (counting all the parents' y)
	*/
	short GlobalY() const;

	/*
	Return the GambeObject's local pivot x position
	*/
	short PivotX() const;
	/*
	Return the GambeObject's local pivot y position
	*/
	short PivotY() const;
	/*
	Return the GambeObject's global pivot x position
	*/
	short GlobalPivotX() const;
	/*
	Return the GambeObject's global pivot y position
	*/
	short GlobalPivotY() const;

	/*
	Return the GambeObject's rotation (counting all the parents' rotations)
	*/
	short GlobalRotation() const;
	/*
	Return the GambeObject's alpha (counting all the parents' alphas)
	*/
	float GlobalA() const;

	/*
	Return the GambeObject's x scale on the screen (counting all the parents' x)
	*/
	float GlobalScaleX() const;
	/*
	Return the GambeObject's y scale on the screen (counting all the parents' y)
	*/
	float GlobalScaleY() const;

	/*
	Return true if the GameObject has to be rendered (also takes count of scale and alpha)
	*/
	bool IsVisible() const;
	/*
	Set if the GameObject has to be rendered (also takes count of scale and alpha)
	*/
	void SetVisibility(bool isVisible);

	/*
	Return true if the GameObject has run events and updates
	*/
	bool IsActive() const;
	/*
	Set if the GameObject has to run events and updates
	*/
	void SetActive(bool isActive);

	/*
	Set the param GameObject as child of the actual GameObject.
	*/
	void AddChild(GameObject* child);
	/*
	Remove the selected child from the GameObject
	*/
	void RemoveChild(GameObject* child);
	/*
	Remove all the children from the GameObject
	*/
	void RemoveChildren();

protected:
	/*
	Function called from the GraphicManager. Return the image to render
	*/
	virtual Image* GetRenderingImage();

	/*
	Function called when the GameObject is initialized
	*/
	virtual void Init();

	/*
	Function called at the first frame of the GameObject
	*/
	virtual void Start();

	/*
	Function called each frame
	*/
	virtual void Update();
};

