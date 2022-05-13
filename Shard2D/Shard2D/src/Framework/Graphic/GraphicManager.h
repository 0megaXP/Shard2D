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

		/*
		Modify the size of the application window (all the objects will be scale in comparison of the default resolution)
		*/
		void ResizeWindow(Uint16 widthResolution, Uint16 heightResolution, WindowType::Type windowType);
		/*
		Set the default resolution for the window.
		@param adaptToResolution: If true, all the entities in the scene will be scaled and moved if the resolution is
		different from the default one, adapting to the new resolution.
		*/
		void SetDefaultResolution(Uint16 defaultWidthResolution, Uint16 defaultHeightResolution, bool adaptToResolution);
		/*
		Return the Horizontal multiplier for the resolution adaptation.
		*/
		float GetHorizontalResolutionAdapter();
		/*
		Return the Vertical multiplier for the resolution adaptation.
		*/
		float GetVerticalResolutionAdapter();

		void DrawDebugRect(Entity* entity);

	private:
		void Init();

		void RenderEntity(Entity* entity);

		void RenderTextureEntity(Entity* _entity, Image* _image);

		void RenderScene();

		void ApplyResize();

		void UpdateResolutionAdapters();
	};
}