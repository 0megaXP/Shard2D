#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class GameObject;

class GraphicManager
{
public:
	GraphicManager();
	~GraphicManager();

	SDL_Window* _window;
	SDL_Surface* _winSurface;

	friend class GameManager;

private:
	void Init();

	void FixPositionForRotation(SDL_Surface* _rotatedSurface, GameObject* _object);
	void FixPositionForParentRotation(SDL_Surface* _rotatedSurface, GameObject* _object);

	void RenderObject(GameObject* object);

	void RenderScene();
};

