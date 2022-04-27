#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

#include "WindowType.h"

namespace Shard2D
{
	struct Image;
	struct SurfaceImage;
	struct TextureImage;
	class Entity;

	class GraphicManager
	{
	private:
		GraphicManager();
		~GraphicManager();

		friend class Managers;

		SDL_Window* _window;

		SDL_Renderer* _winRenderer;

		bool _resizeWindow = false;
		Uint16 _widthResolution = 1280;
		Uint16 _heightResolution = 720;
		std::string _windowName = "Application Name";
		WindowType::Type _windowType = WindowType::Window;

		Uint16 _defaultWidthResolution = 1280;
		Uint16 _defaultHeightResolution = 720;
		float _horizontalAdaptationMultiplier = 1;
		float _verticalAdaptationMultiplier = 1;
		bool _adaptToResolution = false;

		friend class GameManager;

	public:
		/*
		Creates a texture from a given surface
		*/
		SDL_Texture* CreateTexture(SDL_Surface* surface);

		void ResizeWindow(Uint16 widthResolution, Uint16 heightResolution, WindowType::Type windowType);

		void SetDefaultResolution(Uint16 defaultWidthResolution, Uint16 defaultHeightResolution, bool adaptToResolution);

		float GetHorizontalResolutionAdapter();

		float GetVerticalResolutionAdapter();

	private:
		void Init();

		void FixPositionForParentRotation(Entity* _entity);

		void RenderEntity(Entity* entity);

		void RenderTextureEntity(Entity* _entity, Image* _image);

		void RenderScene();

		void ApplyResize();

		void UpdateResolutionAdapters();
	};
}