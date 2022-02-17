#include "GraphicManager.h"

#include <SDL2_rotozoom.h>
#include <SDL_ttf.h>

#include "../Entities/Entity.h"
#include "../Utils/ShardUtils.h"
#include "../Management/Managers.h"
#include "../Events/Event.h"

import MathUtils;

namespace Shard2D
{
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

	void GraphicManager::FixPositionForRotation(SDL_Surface* _rotatedSurface, Entity* _entity, SurfaceImage* _image)
	{
		/*This function is used for fixing the GameObject's position during its rotation. If the centre of the rotation is not the centre of the object,
		its position must be fixed to match the surface upper-left corner with the pivot.*/
		// Saves the original surface width and height (scaled)
		float surfaceW = _image->_surface->w * _entity->GlobalScaleX();
		float surfaceH = _image->_surface->h * _entity->GlobalScaleY();
		// Gets a direction from the object rotation (the standard position for the 0° rotation is at 45°)
		Vector2 normalizedPosition = PositionFromDeg(_entity->GlobalRotation() + 45);
		// Saves a standard direction (used during the x and y calculation)
		Vector2 basePosition = PositionFromDeg(360 - 45);
		// The central point of the circumference used to create each position for its rotation
		Vector2 centre = Vector2(float(_entity->GlobalX() - _rotatedSurface->w / 2), float(_entity->GlobalY() - _rotatedSurface->h / 2));
		float radius = Distance(Vector2(_entity->RenderingX(), _entity->RenderingY()), centre);
		// If the distance between the centre and the rendering position is 0, the object position doesn't need to be fixed
		if (radius > 0)
		{
			// Set the new fixed offset
			_entity->_selfFixedX += short(centre.x + (normalizedPosition.x / basePosition.x) * surfaceW / 2 - _entity->RenderingX());
			_entity->_selfFixedY += short(centre.y - (normalizedPosition.y / basePosition.y) * surfaceH / 2 - _entity->RenderingY());
		}
	}

	void GraphicManager::FixPositionForParentRotation(Entity* _entity)
	{
		/*This function is used for fixing the GameObject's position during its parent's rotation.*/
		if (_entity->Parent() != nullptr)
		{
			// Now the centre of the circumference is the parent global position
			Vector2 centre = Vector2(_entity->Parent()->GlobalX(), _entity->Parent()->GlobalY());
			// Here we must use the global position, because the rendering position is already affected by the selfFixed values
			float radius = Distance(Vector2(_entity->GlobalX(), _entity->GlobalY()), centre);
			if (radius > 0)
			{
				Vector2 _objectLocalPosition = Vector2(_entity->x, _entity->y);

				int _objectActualRotation = int(DegFromPosition(_objectLocalPosition, Vector2()));
				Vector2 normalizedPosition = PositionFromDeg(_entity->Parent()->GlobalRotation() + _objectActualRotation);
				Vector2 basePosition = PositionFromDeg(0);

				_entity->_parentFixedX += short(normalizedPosition.x * radius - _entity->x);
				_entity->_parentFixedY += short(normalizedPosition.y * radius - _entity->y);
			}
		}
	}

	void GraphicManager::RenderEntity(Entity* _entity)
	{
		if (_entity->IsVisible())
		{
			Image* _entityImage = _entity->GetRenderingImage();

			if (_entityImage != nullptr)
			{
#if RENDERING_TYPE == TEXTURE_RENDERING
				if (_entityImage->type == TEXTURE_TYPE)
				{
					RenderTextureEntity(_entity, static_cast<TextureImage*>(_entityImage));
				}
#else
				if (_objectImage->type == SURFACE_TYPE)
				{
					RenderSurfaceEntity(_object, static_cast<SurfaceImage*>(_objectImage));
				}
#endif
			}

			// Call the RenderObject() function for all the children
			for (Entity* child : _entity->_children)
			{
				RenderEntity(child);
			}
		}
	}

#if RENDERING_TYPE == TEXTURE_RENDERING
	void GraphicManager::RenderTextureEntity(Entity* _entity, TextureImage* _image)
	{
		if (_image && _image->_texture)
		{
			_entity->ResetFixedValues();

			SDL_Texture* texture = _image->_texture;

			// Managing the pivot
			if (_entity->centerPivot)
			{
				_entity->_pivotOffsetX = short(_image->_width / -2 * _entity->GlobalScaleX());
				_entity->_pivotOffsetY = short(_image->_height / -2 * _entity->GlobalScaleY());
			}

			SDL_Point rotPoint = SDL_Point();
			rotPoint.x = -_entity->_pivotOffsetX;
			rotPoint.y = -_entity->_pivotOffsetY;

			FixPositionForParentRotation(_entity);

			// Set the final rendering position for future needs
			if (_entity->GlobalRotation() != 0 && _entity->centerPivot)
			{
				// Adjust the position with the rotation of the texture
				_entity->_finalFixedX = (short)(_entity->RenderingX() - _entity->_pivotOffsetX + PositionFromDeg(225 + _entity->GlobalRotation()).x * _entity->width / 2 * _entity->GlobalScaleX() / -PositionFromDeg(225).x);
				_entity->_finalFixedY = (short)(_entity->RenderingY() - _entity->_pivotOffsetY + PositionFromDeg(225 + _entity->GlobalRotation()).y * _entity->height / 2 * _entity->GlobalScaleY() / -PositionFromDeg(225).y);
			}
			else
			{
				_entity->_finalFixedX = _entity->RenderingX();
				_entity->_finalFixedY = _entity->RenderingY();
			}

			// Setting the rendering rect
			SDL_Rect _tempRect = SDL_Rect();
			_tempRect.x = int(_entity->RenderingX());
			_tempRect.y = int(_entity->RenderingY());
			_tempRect.w = int(_image->_width * _entity->GlobalScaleX());
			_tempRect.h = int(_image->_height * _entity->GlobalScaleY());

			SDL_SetTextureAlphaMod(_image->_texture, Uint8(_entity->GlobalA() * 255));
			SDL_SetTextureColorMod(_image->_texture, _entity->color.r, _entity->color.g, _entity->color.b);
			SDL_RenderCopyEx(_winRenderer, _image->_texture, NULL, &_tempRect, _entity->GlobalRotation(), &rotPoint, SDL_FLIP_NONE);
			_entity->DispatchEvent<Event>(Event::Rendered);
		}
	}
#else
	void GraphicManager::RenderSurfaceEntity(Entity* _entity, SurfaceImage* _image)
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

			_object->_finalFixedX = _object->RenderingX();
			_object->_finalFixedY = _object->RenderingY();

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

		for (Entity* entity : M_EntitiesManager->_stagedEntities)
		{
			RenderEntity(entity);
		}

#if RENDERING_TYPE == TEXTURE_RENDERING
		SDL_RenderPresent(_winRenderer);
#else
		// Refresh the window for all the new objects to render
		SDL_UpdateWindowSurface(_window);
#endif
	}
}