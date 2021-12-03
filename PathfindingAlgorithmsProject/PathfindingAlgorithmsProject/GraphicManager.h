#pragma once

#include <SDL.h>
#include <vector>

class GameObject;

class GraphicManager
{
public:
	GraphicManager();

private:
	~GraphicManager();

	SDL_Window* window;
	SDL_Surface* winSurface;

	std::vector<GameObject*> _stagedObjects;

	std::vector<GameObject*> _unusedObjects;

public:
	bool Init();

	static void AddObjectToStage(GameObject* object);
	static void RemoveObjectFromStage(GameObject* object);

private:
	void SetObjectUnused(GameObject* object);
	void UnsetObjectUnused(GameObject* object);
};

