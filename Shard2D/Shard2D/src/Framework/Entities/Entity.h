#pragma once

#include <string>
#include <vector>

#include "../Graphic/Image.h"

#include "../Events/EventDispatcher.h"

class Entity : public EventDispatcher
{
public:
	Entity();
	virtual ~Entity();

	friend class GraphicManager;
	friend class EntitiesManager;
	friend class GameManager;
	friend class EventsManager;

private:
	std::string _name = "";
	Entity* _parent = nullptr;
	std::vector<Entity*> _children;

	bool _visible = true;
	bool _active = true;

	short _parentFixedX = 0;
	short _parentFixedY = 0;

	short _selfFixedX = 0;
	short _selfFixedY = 0;

	short _pivotOffsetX = 0;
	short _pivotOffsetY = 0;

	bool mouseOverlapped = false;

	short _finalFixedX = 0;
	short _finalFixedY = 0;

public:
	std::string Name() const;
	Entity* Parent() const;

	float x = 0;
	float y = 0;

	float width = 0;
	float height = 0;

	float rotation = 0;

	float a = 1;

	float scaleX = 1;
	float scaleY = 1;

	bool centerPivot = false;

	bool mouseEnabled = true;
	bool blockMouseEvents = true;

	SDL_Color color = SDL_Color(255, 255, 255);

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
	Return the GambeObject's x rendering position (using all the fixed positions and offsets)
	*/
	short RenderingX() const;
	/*
	Return the GambeObject's y rendering position (using all the fixed positions and offsets)
	*/
	short RenderingY() const;

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
	float GlobalRotation() const;
	/*
	Return the GambeObject's alpha (counting all the parents' alphas)
	*/
	float GlobalA() const;

	/*
	Return the GambeObject's x scale on the screen (counting all the parents' x)
	*/
	virtual float GlobalScaleX() const;
	/*
	Return the GambeObject's y scale on the screen (counting all the parents' y)
	*/
	virtual float GlobalScaleY() const;

	/*
	Return true if the Entity has to be rendered (also takes count of scale and alpha)
	*/
	bool IsVisible() const;
	/*
	Set if the Entity has to be rendered (also takes count of scale and alpha)
	*/
	void SetVisibility(bool isVisible);

	/*
	Return true if the Entity has run events and updates
	*/
	bool IsActive() const;
	/*
	Set if the Entity has to run events and updates
	*/
	void SetActive(bool isActive);

	/*
	Set the param Entity as child of the actual Entity.
	*/
	void AddChild(Entity* child);
	/*
	Remove the selected child from the Entity
	*/
	void RemoveChild(Entity* child);
	/*
	Remove all the children from the Entity
	*/
	void RemoveChildren();

protected:
	/*
	Function called from the GraphicManager. Return the image to render
	*/
	virtual Image* GetRenderingImage();

	std::shared_ptr<Image> _image;

	/*
	Function called when the Entity is initialized
	*/
	virtual void Init() {};

	/*
	Function called each frame
	*/
	virtual void Update() {};
};

