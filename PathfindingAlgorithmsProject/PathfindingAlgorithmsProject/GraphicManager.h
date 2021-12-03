#pragma once

#include <SDL.h>

class GameObject;

class GraphicManager
{
public:
	GraphicManager();

private:
	~GraphicManager();

	SDL_Window* window;
	SDL_Surface* winSurface;

	static GameObject* _gameStage;

public:
	bool Init();

	GameObject* GetStage() const;
};

