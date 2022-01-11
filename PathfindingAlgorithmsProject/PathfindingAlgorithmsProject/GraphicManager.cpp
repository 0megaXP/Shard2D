#include "GraphicManager.h"

#include <SDL_image.h>
#include <SDL.h>
#include <SDL2_rotozoom.h>

#include "Managers.h"
#include "AssetsManager.h"
#include "GameObjectsManager.h"
#include "GameObject.h"
#include "Image.h"
#include "CustomIOStream.h"

GraphicManager::GraphicManager()
	: _window(nullptr), _winSurface(nullptr)
{
	Init();
}

GraphicManager::~GraphicManager()
{
	// Destroy the app window and call the SDL destructor
	SDL_DestroyWindow(_window);
	SDL_Quit();

	Log("SDL exit correctly!", TextColor::Green);
}

void GraphicManager::Init()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		Log("Error initializing SDL: " + *SDL_GetError(), TextColor::Red);
		system("pause");
		return;
	}

	_window = SDL_CreateWindow("MainWIndow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if (!_window)
	{
		Log("Error creating window: " + *SDL_GetError(), TextColor::Red);
		system("pause");
		return;
	}

	_winSurface = SDL_GetWindowSurface(_window);
	if (!_winSurface)
	{
		Log("Error getting surface: " + *SDL_GetError(), TextColor::Red);
		system("pause");
		return;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "Error initializing SDL_image with png: " << IMG_GetError << std::endl;
	}

	Log("SDL initialized correctly!", TextColor::Green);

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
		
		SDL_SetSurfaceAlphaMod(objectSurface->_surface, (object->GlobalA() * 255));

		SDL_Surface* rotatedSurface = rotozoomSurface(objectSurface->_surface, object->GlobalRotation(), 1, 0);
		// TODO Fix the rotation zoom in and the centre position for the child

		SDL_BlitScaled(rotatedSurface, NULL, _winSurface, &tempRect);

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
