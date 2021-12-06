#include "GraphicManager.h"

#include <iostream>

#include "GameObject.h"

GraphicManager::GraphicManager()
{
	_window = nullptr;
	_winSurface = nullptr;

	_stagedObjects = std::vector<GameObject*>();
	_unusedObjects = std::vector<GameObject*>();

	Init();
}

GraphicManager::~GraphicManager()
{
}

void GraphicManager::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return;
	}

	_window = SDL_CreateWindow("MainWIndow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if (!_window)
	{
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return;
	}

	_winSurface = SDL_GetWindowSurface(_window);
	if (!_winSurface)
	{
		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
		system("pause");
		return;
	}

	// Set the background color
	SDL_FillRect(_winSurface, NULL, SDL_MapRGB(_winSurface->format, 0, 0, 0));
	SDL_UpdateWindowSurface(_window);
	return;
}

void GraphicManager::AddObjectToStage(GameObject* object)
{
	_stagedObjects.push_back(object);
	UnsetObjectUnused(object);
	if (object->Parent() != nullptr)
	{
		object->_parent->RemoveChild(object);
	}

	for (GameObject* child : object->_children)
	{
		UnsetObjectUnused(child);
	}

}

void GraphicManager::RemoveObjectFromStage(GameObject* object)
{
	int count = 0;
	for (GameObject* stagedObject : _stagedObjects)
	{
		if (object == stagedObject)
		{
			_stagedObjects.erase(_stagedObjects.begin() + count);
			SetObjectUnused(object);
			for (GameObject* child : object->_children)
			{
				SetObjectUnused(child);
			}
			return;
		}
		count++;
	}
}

void GraphicManager::ChildAdded(GameObject* child)
{
	UnsetObjectUnused(child);
}

void GraphicManager::ChildRemoved(GameObject* child)
{
	SetObjectUnused(child);
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
