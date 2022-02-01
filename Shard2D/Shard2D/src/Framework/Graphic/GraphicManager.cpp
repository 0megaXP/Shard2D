#include "GraphicManager.h"

#include <SDL2_rotozoom.h>
#include <SDL_ttf.h>

#include "../GameObjects/GameObject.h"
#include "../Utils/ShardUtils.h"
#include "../Management/Managers.h"
#include "../Events/Event.h"

import MathUtils;

GraphicManager::GraphicManager()
{
	Init();
}

GraphicManager::~GraphicManager()
{
	// Destroy the app window and call the SDL destructor
	SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	Log("SDL exit correctly!", TextColor::Green);
}

SDL_Texture* GraphicManager::CreateTexture(SDL_Surface* surface)
{
	return SDL_CreateTextureFromSurface(_winRenderer, surface);
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

#if RENDERING_TYPE == TEXTURE_RENDERING
	_winRenderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_winRenderer) 
	{
		Log("Failed to create window and renderer: " + *SDL_GetError(), TextColor::Red);
	}
#else
	_winSurface = SDL_GetWindowSurface(_window);
	if (!_winSurface)
	{
		Log("Error getting surface: " + *SDL_GetError(), TextColor::Red);
		system("pause");
		return;
	}
#endif


	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "Error initializing SDL_image with png: " << IMG_GetError << std::endl;
	}

	if (TTF_Init() < 0) 
	{
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
	}

	Log("SDL initialized correctly!", TextColor::Green);

#if RENDERING_TYPE == TEXTURE_RENDERING
	SDL_SetRenderDrawColor(_winRenderer, 0, 0, 0, 255);
#else
	SDL_FillRect(_winSurface, NULL, SDL_MapRGB(_winSurface->format, 0, 0, 0));
#endif
	SDL_UpdateWindowSurface(_window);
	return;
}

void GraphicManager::FixPositionForRotation(SDL_Surface* _rotatedSurface, GameObject* _object, SurfaceImage* _image)
{
	/*This function is used for fixing the GameObject's position during its rotation. If the centre of the rotation is not the centre of the object, 
	its position must be fixed to match the surface upper-left corner with the pivot.*/
	// Saves the original surface width and height (scaled)
	float surfaceW = _image->_surface->w * _object->GlobalScaleX();
	float surfaceH = _image->_surface->h * _object->GlobalScaleY();
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

void GraphicManager::FixPositionForParentRotation(GameObject* _object)
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

			_object->_parentFixedX += normalizedPosition.x * radius - _object->x ;//+ _object->Parent()->GlobalParentFixedX();
			_object->_parentFixedY += normalizedPosition.y * radius - _object->y ;//+ _object->Parent()->GlobalParentFixedY();
		}
	}
}

void GraphicManager::RenderObject(GameObject* _object)
{
	if (_object->IsVisible())
	{
		Image* _objectImage = _object->GetRenderingImage();

		if (_objectImage != nullptr)
		{
#if RENDERING_TYPE == TEXTURE_RENDERING
			if (_objectImage->type == TEXTURE_TYPE)
			{
				RenderTextureObject(_object, static_cast<TextureImage*>(_objectImage));
			}
#else
			if (_objectImage->type == SURFACE_TYPE)
			{
				RenderSurfaceObject(_object, static_cast<SurfaceImage*>(_objectImage));
			}
#endif
		}
		
		// Call the RenderObject() function for all the children
		for (GameObject* child : _object->_children)
		{
			RenderObject(child);
		}
	}
}

#if RENDERING_TYPE == TEXTURE_RENDERING
void GraphicManager::RenderTextureObject(GameObject* _object, TextureImage* _image)
{
	if (_image && _image->_texture)
	{
		_object->ResetFixedValues();

		SDL_Texture* texture = _image->_texture;
		int textureW, textureH, access;
		unsigned int format;
		SDL_QueryTexture(_image->_texture, &format, &access, &textureW, &textureH);

		// Managing the pivot
		if (_object->centerPivot)
		{
			_object->_pivotOffsetX = textureW / -2 * _object->GlobalScaleX();
			_object->_pivotOffsetY = textureH / -2 * _object->GlobalScaleY();
		}

		SDL_Point rotPoint = SDL_Point();
		rotPoint.x = -_object->_pivotOffsetX;
		rotPoint.y = -_object->_pivotOffsetY;

		FixPositionForParentRotation(_object);

		// Setting the rendering rect
		SDL_Rect _tempRect = SDL_Rect();
		_tempRect.x = _object->RenderingX();
		_tempRect.y = _object->RenderingY();
		_tempRect.w = textureW * _object->GlobalScaleX();
		_tempRect.h = textureH * _object->GlobalScaleY();

		SDL_SetTextureAlphaMod(_image->_texture, _object->GlobalA() * 255);

		SDL_RenderCopyEx(_winRenderer, _image->_texture, NULL, &_tempRect, _object->GlobalRotation(), &rotPoint, SDL_FLIP_NONE);
		_object->DispatchEvent(Event::Rendered);
	}
}
#else
void GraphicManager::RenderSurfaceObject(GameObject* _object, SurfaceImage* _image)
{
	if (_image && _image->_surface)
	{
		_object->ResetFixedValues();

		// Setting the alpha on the surface
		SDL_SetSurfaceAlphaMod(_image->_surface, (_object->GlobalA() * 255));
		// Setting the scale
		SDL_Surface* _scaledSurface = zoomSurface(_image->_surface, _object->GlobalScaleX(), _object->GlobalScaleY(), 0);
		// Setting the rotation
		SDL_Surface* _rotatedSurface = rotozoomSurface(_scaledSurface, -_object->GlobalRotation(), 1, 0);

		// Managing the pivot
		if (_object->centerPivot)
		{
			_object->_pivotOffsetX = -_rotatedSurface->w / 2;
			_object->_pivotOffsetY = -_rotatedSurface->h / 2;
		}
		// Fixing the object position during the rotation
		FixPositionForRotation(_rotatedSurface, _object, _image);
		// Fix the position also based on the parent rotation and fixed position
		FixPositionForParentRotation(_object);

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
		_object->DispatchEvent(Event::Rendered);
	}
}
#endif

void GraphicManager::RenderScene()
{
#if RENDERING_TYPE == TEXTURE_RENDERING
	SDL_SetRenderDrawColor(_winRenderer, 0, 0, 0, 255);
	SDL_RenderClear(_winRenderer);
#else
	SDL_FillRect(_winSurface, NULL, SDL_MapRGB(_winSurface->format, 0, 0, 0));
#endif

	for (GameObject* object : M_GameObjectsManager->_stagedObjects)
	{
		RenderObject(object);
	}

#if RENDERING_TYPE == TEXTURE_RENDERING
	SDL_RenderPresent(_winRenderer);
#else
	// Refresh the window for all the new objects to render
	SDL_UpdateWindowSurface(_window);
#endif
}
