#include "GraphicManager.h"

#include <SDL2_rotozoom.h>
#include <SDL_ttf.h>

#include "../Entities/Entity.h"
#include "../Utils/ShardUtils.h"
#include "../Management/Managers.h"
#include "../Events/EventTypes/Event.h"

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

	void GraphicManager::ResizeWindow(Uint16 widthResolution, Uint16 heightResolution, WindowType::Type windowType)
	{
		if (widthResolution != _widthResolution ||
			heightResolution != _heightResolution ||
			windowType != _windowType)
		{
			_widthResolution = widthResolution;
			_heightResolution = heightResolution;
			_windowType = windowType;
			_resizeWindow = true;
		}
	}

	void GraphicManager::SetDefaultResolution(Uint16 defaultWidthResolution, Uint16 defaultHeightResolution, bool adaptToResolution)
	{
		if (defaultWidthResolution > 0 &&
			defaultHeightResolution > 0)
		{
			_defaultWidthResolution = defaultWidthResolution;
			_defaultHeightResolution = defaultHeightResolution;
			_adaptToResolution = adaptToResolution;
		}

		UpdateResolutionAdapters();
	}

	float GraphicManager::GetHorizontalResolutionAdapter()
	{
		return _horizontalAdaptationMultiplier;
	}

	float GraphicManager::GetVerticalResolutionAdapter()
	{
		return _verticalAdaptationMultiplier;
	}

	void GraphicManager::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			Log("Error initializing SDL: " + *SDL_GetError(), TextColor::Red);
			system("pause");
			return;
		}

		_window = SDL_CreateWindow(_windowName.c_str() , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _widthResolution, _heightResolution, _windowType);
		if (!_window)
		{
			Log("Error creating window: " + *SDL_GetError(), TextColor::Red);
			system("pause");
			return;
		}

		_winRenderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
		if (!_winRenderer)
		{
			Log("Failed to create window and renderer: " + *SDL_GetError(), TextColor::Red);
		}


		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			std::cout << "Error initializing SDL_image with png: " << IMG_GetError << std::endl;
		}

		if (TTF_Init() < 0)
		{
			std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
		}

		Log("SDL initialized correctly!", TextColor::Green);

		SDL_SetRenderDrawColor(_winRenderer, 0, 0, 0, 255);
		SDL_UpdateWindowSurface(_window);
		return;
	}

	void GraphicManager::FixPositionForParentRotation(Entity* _entity)
	{
		/*This function is used for fixing the GameObject's position during its parent's rotation.*/
		if (_entity->Parent() != nullptr)
		{
			// Now the centre of the circumference is the parent global position
			Vector2 centre = Vector2(_entity->Parent()->GlobalX() + _entity->Parent()->GlobalScaleFixedX(), _entity->Parent()->GlobalY() + _entity->Parent()->GlobalScaleFixedY());
			// Here we must use the global position, because the rendering position is already affected by the selfFixed values
			float radius = Distance(Vector2(_entity->GlobalX() + _entity->GlobalScaleFixedX(), _entity->GlobalY() + _entity->GlobalScaleFixedY()), centre);
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
				RenderTextureEntity(_entity, _entityImage);
			}

			// Call the RenderObject() function for all the children
			for (Entity* child : _entity->_children)
			{
				RenderEntity(child);
			}
		}
	}

	void GraphicManager::RenderTextureEntity(Entity* _entity, Image* _image)
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

	void GraphicManager::RenderScene()
	{
		if (_resizeWindow)
			ApplyResize();

		SDL_SetRenderDrawColor(_winRenderer, 0, 0, 0, 255);
		SDL_RenderClear(_winRenderer);

		for (Entity* entity : M_EntitiesManager->_stagedEntities)
		{
			RenderEntity(entity);
		}

		SDL_RenderPresent(_winRenderer);
	}

	void GraphicManager::ApplyResize()
	{
		SDL_SetWindowSize(_window, _widthResolution, _heightResolution);
		SDL_SetWindowFullscreen(_window, _windowType);
		SDL_SetWindowTitle(_window, _windowName.c_str());

		SDL_SetRenderDrawColor(_winRenderer, 0, 0, 0, 255);
		SDL_UpdateWindowSurface(_window);

		_resizeWindow = false;
		UpdateResolutionAdapters();
	}

	void GraphicManager::UpdateResolutionAdapters()
	{
		if (_adaptToResolution)
		{
			_horizontalAdaptationMultiplier = (float)_widthResolution / (float)_defaultWidthResolution;
			_verticalAdaptationMultiplier = (float)_heightResolution / (float)_defaultHeightResolution;
		}
		else
		{
			_horizontalAdaptationMultiplier = 1;
			_verticalAdaptationMultiplier = 1;
		}
		Log(_horizontalAdaptationMultiplier, TextColor::Yellow);
	}
}