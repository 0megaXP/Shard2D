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

	_window = SDL_CreateWindow("Pathfinding Algorithms Evaluation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
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

void GraphicManager::FixPositionForRotation(SDL_Surface* _rotatedSurface, GameObject* _object)
{
	/*This function is used for fixing the GameObject's position during its rotation. If the centre of the rotation is not the centre of the object, 
	its position must be fixed to match the surface upper-left corner with the pivot.*/
	// Saves the original surface width and height (scaled)
	float surfaceW = _object->GetRenderingImage()->_surface->w * _object->GlobalScaleX();
	float surfaceH = _object->GetRenderingImage()->_surface->h * _object->GlobalScaleY();
	// Gets a direction from the object rotation (the standard position for the 0° rotation is at 45°)
	Vector2 normalizedPosition = PositionFromDeg(_object->GlobalRotation() + 45);
	// Saves a standard direction (used during the x and y calculation)
	Vector2 basePosition = PositionFromDeg(360 - 45);
	// The central point of the circumference used to create each position for its rotation
	Vector2 centre = Vector2(_object->GlobalX() - _rotatedSurface->w / 2, _object->GlobalY() - _rotatedSurface->h / 2);
	float radius = Distance(Vector2(_object->RenderingX(), _object->RenderingY()), centre);
	// If the distance between the centre and the rendering position is 0, the object position doesn't need to be fixed
	if (radius > 0)
	{
		// Set the new fixed offset
		_object->_selfFixedX += centre.x + (normalizedPosition.x / basePosition.x) * surfaceW / 2 - _object->RenderingX();
		_object->_selfFixedY += centre.y - (normalizedPosition.y / basePosition.y) * surfaceH / 2 - _object->RenderingY();
	}
}

void GraphicManager::FixPositionForParentRotation(SDL_Surface* _rotatedSurface, GameObject* _object)
{
	/*This function is used for fixing the GameObject's position during its parent's rotation.*/
	if (_object->Parent() != nullptr)
	{
		// Now the centre of the circumference is the parent global position
		Vector2 centre = Vector2(_object->Parent()->GlobalX(), _object->Parent()->GlobalY());
		// Here we must use the global position, because the rendering position is already affected by the selfFixed values
		float radius = Distance(Vector2(_object->GlobalX(), _object->GlobalY()), centre);
		if (radius > 0)
		{
			Vector2 _objectLocalPosition = Vector2(_object->x, _object->y);

			int _objectActualRotation = DegFromPosition(_objectLocalPosition, Vector2());
			Vector2 normalizedPosition = PositionFromDeg(_object->Parent()->GlobalRotation() + _objectActualRotation);
			Vector2 basePosition = PositionFromDeg(0);

			_object->_parentFixedX += normalizedPosition.x * radius - _object->x + _object->Parent()->GlobalParentFixedX();
			_object->_parentFixedY += normalizedPosition.y * radius - _object->y + _object->Parent()->GlobalParentFixedY();
		}
	}
}

void GraphicManager::RenderObject(GameObject* _object)
{
	if (_object->IsVisible())
	{
		Image* _objectImage = _object->GetRenderingImage(); 
		_object->ResetFixedValues();

		// Setting the alpha on the surface
		SDL_SetSurfaceAlphaMod(_objectImage->_surface, (_object->GlobalA() * 255));
		// Setting the scale
		SDL_Surface* _scaledSurface = zoomSurface(_objectImage->_surface, _object->GlobalScaleX(), _object->GlobalScaleY(), 0);
		// Setting the rotation
		SDL_Surface *_rotatedSurface = rotozoomSurface(_scaledSurface, -_object->GlobalRotation(), 1, 0);

		// Managing the pivot
		if (_object->centerPivot)
		{
			_object->_pivotOffsetX = -_rotatedSurface->w / 2;
			_object->_pivotOffsetY = -_rotatedSurface->h / 2;
		}
		// Fixing the object position during the rotation
		FixPositionForRotation(_rotatedSurface, _object);
		// Fix the position also based on the parent rotation and fixed position
		FixPositionForParentRotation(_rotatedSurface, _object);

		// Setting the rendering rect
		SDL_Rect _tempRect = SDL_Rect();
		_tempRect.x = _object->RenderingX();
		_tempRect.y = _object->RenderingY();
		_tempRect.w = _rotatedSurface->w;
		_tempRect.h = _rotatedSurface->h;

		// Rendering the surface
		SDL_BlitSurface(_rotatedSurface, NULL, _winSurface, &_tempRect);
		// Freeing all the surfaces created in this stack
		SDL_FreeSurface(_scaledSurface);
		SDL_FreeSurface(_rotatedSurface);
		// Call the RenderObject() function for all the children
		for (GameObject* child : _object->_children)
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
