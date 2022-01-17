#include "GraphicManager.h"

#include <SDL_image.h>
#include <SDL.h>
#include <SDL2_rotozoom.h>
#include <math.h>

#include "Managers.h"
#include "AssetsManager.h"
#include "GameObjectsManager.h"
#include "GameObject.h"
#include "Image.h"
#include "CustomIOStream.h"
#include "MathVectors.h"

import MathUtils;

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

void GraphicManager::FixPositionForRotation(SDL_Rect& _tempRect, SDL_Surface* _rotatedSurface, GameObject* _object)
{
	float surfaceW = _object->GetRenderingImage()->_surface->w * _object->GlobalScaleX();
	float surfaceH = _object->GetRenderingImage()->_surface->h * _object->GlobalScaleY();
	Vector2 normalizedPosition = PositionFromDeg(_object->GlobalRotation() + 45);
	Vector2 basePosition = PositionFromDeg(360 - 45);
	Vector2 centre = Vector2(_object->GlobalX() - _rotatedSurface->w / 2, _object->GlobalY() - _rotatedSurface->h / 2);
	float radius = Distance(Vector2(_tempRect.x, _tempRect.y), centre);
	if (radius > 0)
	{
		_object->fixedOffsetX = centre.x + (normalizedPosition.x / basePosition.x) * surfaceW / 2 - _tempRect.x;
		_object->fixedOffsetY = centre.y - (normalizedPosition.y / basePosition.y) * surfaceH / 2 - _tempRect.y;

		_tempRect.x += _object->GlobalFixedOffsetX();
		_tempRect.y += _object->GlobalFixedOffsetY();
	}
}

void GraphicManager::RenderObject(GameObject* object)
{
	if (object->IsVisible())
	{
		Image* _objectImage = object->GetRenderingImage();

		// Setting the alpha on the surface
		SDL_SetSurfaceAlphaMod(_objectImage->_surface, (object->GlobalA() * 255));
		// Setting the scale
		SDL_Surface* _scaledSurface = zoomSurface(_objectImage->_surface, object->GlobalScaleX(), object->GlobalScaleY(), 0);
		// Setting the rotation
		SDL_Surface *_rotatedSurface = rotozoomSurface(_scaledSurface, -object->GlobalRotation(), 1, 0);

		// Setting the rendering rect
		SDL_Rect _tempRect = SDL_Rect();
		_tempRect.x = object->GlobalX();
		_tempRect.y = object->GlobalY();
		_tempRect.w = _rotatedSurface->w;
		_tempRect.h = _rotatedSurface->h;
		// Managing the pivot
		if (object->centerPivot)
		{
			_tempRect.x -= _tempRect.w / 2;
			_tempRect.y -= _tempRect.h / 2;
		}
		// TODO Fix the position also based on the parent rotation and fixed position
		// Fixing the object position during the rotation
		FixPositionForRotation(_tempRect, _rotatedSurface, object);

		// Rendering the surface
		SDL_BlitSurface(_rotatedSurface, NULL, _winSurface, &_tempRect);
		SDL_FreeSurface(_scaledSurface);
		SDL_FreeSurface(_rotatedSurface);
		// Call the RenderObject() function for all the children
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

	for (GameObject* object : M_GameObjectsManager->_stagedObjects)
	{
		RenderObject(object);
	}

	// Refresh the window for all the new objects to render
	SDL_UpdateWindowSurface(_window);
}
