#include "GraphicManager.h"
#include <iostream>

GraphicManager::GraphicManager()
{
	window = nullptr;
	winSurface = nullptr;

	_stagedObjects = std::vector<GameObject*>();
	_unusedObjects = std::vector<GameObject*>();
}

GraphicManager::~GraphicManager()
{
}

bool GraphicManager::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	window = SDL_CreateWindow("MainWIndow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if (!window) 
	{
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	winSurface = SDL_GetWindowSurface(window);
	if (!winSurface) 
	{
		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	// Set the background color
	SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 0, 0, 0));
	SDL_UpdateWindowSurface(window);
	return true;
}

void GraphicManager::AddObjectToStage(GameObject* object)
{

}

void GraphicManager::RemoveObjectFromStage(GameObject* object)
{

}

void GraphicManager::SetObjectUnused(GameObject* object)
{
	// Check if the object to add is already unused
	for (GameObject* unusedObject : _unusedObjects)
	{
		if (unusedObject == object)
			return;
	}

	_unusedObjects.push_back(object);
}

void GraphicManager::UnsetObjectUnused(GameObject* object)
{
	int count = 0;
	for (GameObject* unusedObject : _unusedObjects)
	{
		if (unusedObject == object)
		{
			_unusedObjects.erase(_unusedObjects.begin() + count);
			return;
		}

		count++;
	}
}
