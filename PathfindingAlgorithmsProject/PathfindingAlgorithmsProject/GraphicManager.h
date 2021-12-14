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

	friend class GameManager;

private:
	void Init();

	void RenderObject(GameObject* object);

	void RenderScene();
};

