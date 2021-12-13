#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class GameObject;

class GraphicManager
{
public:
	GraphicManager();

private:
	~GraphicManager();

	SDL_Window* _window;
	SDL_Surface* _winSurface;

	std::vector<GameObject*> _stagedObjects;

	std::vector<GameObject*> _unusedObjects;

	friend class GameManager;

public:
	void AddObjectToStage(GameObject* object);
	void RemoveObjectFromStage(GameObject* object);

	void ChildAdded(GameObject* child);
	void ChildRemoved(GameObject* child);

private:
	void Init();

	void SetObjectUnused(GameObject* object);
	void UnsetObjectUnused(GameObject* object);

	void RenderScene();
};

