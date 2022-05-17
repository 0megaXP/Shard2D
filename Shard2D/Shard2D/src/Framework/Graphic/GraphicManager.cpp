#include "GraphicManager.h"

#include <SDL2_rotozoom.h>
#include <SDL_ttf.h>

#include "../Entities/Entity.h"
#include "../Entities/EntityDataParser.h"
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

	void GraphicManager::DrawDebugRect(Entity* entity)
	{
		float rotation = entity->GlobalRotation();
		float width = entity->_finalFixedWidth * GetHorizontalResolutionAdapter();
		float height = entity->_finalFixedHeight * GetVerticalResolutionAdapter();
		Vector2 origin = Vector2(entity->_finalFixedX * GetHorizontalResolutionAdapter(), entity->_finalFixedY * GetVerticalResolutionAdapter());
		Vector2 rectPoints[4];

		GenerateRect(rectPoints, origin, width, height, rotation, entity->centerPivot);

		SDL_SetRenderDrawColor(_winRenderer, 255, 0, 0, 255);

		for (int i = 0; i < 4; i++)
		{
			int j = i + 1;
			if (j == 4)
				j = 0;

			SDL_RenderDrawLine(_winRenderer, rectPoints[i].x, rectPoints[i].y, rectPoints[j].x, rectPoints[j].y);
		}

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

	void GraphicManager::RenderEntity(Entity* _entity)
	{
		if (_entity->IsVisible())
		{
			Image* _entityImage = _entity->GetRenderingImage();

			if (_entityImage != nullptr)
			{
				RenderTextureEntity(_entity, _entityImage);
				if(_entity->showDebugRect)
					M_GraphicManager->DrawDebugRect(_entity);
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
			//_entity->ResetFixedValues();

			SDL_Texture* texture = _image->_texture;

			SDL_Point rotPoint = EntityDataParser::GetRotationPoint(_entity, _image);

			// Setting the rendering rect
			SDL_Rect _tempRect = EntityDataParser::GetRenderingRect(_entity, _image);

			Uint8 alpha = EntityDataParser::GetRenderingAlpha(_entity);

			SDL_SetTextureAlphaMod(_image->_texture, alpha);
			SDL_SetTextureColorMod(_image->_texture, _entity->color.r, _entity->color.g, _entity->color.b);
			SDL_RenderCopyEx(_winRenderer, _image->_texture, NULL, &_tempRect, _entity->GlobalRotation(), &rotPoint, SDL_FLIP_NONE);
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