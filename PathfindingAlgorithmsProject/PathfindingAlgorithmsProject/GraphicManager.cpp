#include "GraphicManager.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>

#include "Managers.h"
#include "AssetsManager.h"
#include "GameObjectsManager.h"
#include "GameObject.h"
#include "Image.h"

GraphicManager::GraphicManager()
{
	_window = nullptr;
	_winSurface = nullptr;

	Init();
}

GraphicManager::~GraphicManager()
{
	// Destroy the app window and call the SDL destructor
	SDL_DestroyWindow(_window);
	SDL_Quit();
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

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "Error initializing SDL_image with png: " << IMG_GetError << std::endl;
	}

	// Set the background color
	SDL_FillRect(_winSurface, NULL, SDL_MapRGB(_winSurface->format, 0, 0, 0));
	SDL_UpdateWindowSurface(_window);
	return;
}

void GraphicManager::RenderObject(GameObject* object)
{
	if (object->IsVisible())
	{
		Image* objectSurface = object->GetRenderingImage();

		SDL_Rect tempRect = SDL_Rect();
		tempRect.x = object->GlobalX();
		tempRect.y = object->GlobalY();

		tempRect.w = object->GlobalScaleX() * objectSurface->_surface->w;
		tempRect.h = object->GlobalScaleY() * objectSurface->_surface->h;
		
		// TODO alpha management
		SDL_SetSurfaceAlphaMod(objectSurface->_surface, (object->GlobalA() * 255));

		SDL_BlitScaled(objectSurface->_surface, NULL, _winSurface, &tempRect);

		for (GameObject* child : object->_children)
		{
			RenderObject(child);
		}
	}
}

void GraphicManager::RenderScene()
{
	// Refresh the screen
	SDL_FillRect(_winSurface, NULL, SDL_MapRGB(_winSurface->format, 0, 0, 0));

	for (GameObject* object : Managers::gameObjectsManager->_stagedObjects)
	{
		RenderObject(object);
	}

	// Refresh the window for all the new objects to render
	SDL_UpdateWindowSurface(_window);
}
