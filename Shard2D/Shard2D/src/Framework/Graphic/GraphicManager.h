#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

namespace Shard2D
{
	struct Image;
	struct SurfaceImage;
	struct TextureImage;
	class Entity;

#define SURFACE_RENDERING 0
#define TEXTURE_RENDERING 1

	// Must be SURFACE_RENDERING or TEXTURE_RENDERING
#define RENDERING_TYPE TEXTURE_RENDERING

	class GraphicManager
	{
	private:
		GraphicManager();
		~GraphicManager();

		friend class Managers;

		SDL_Window* _window;
#if RENDERING_TYPE == TEXTURE_RENDERING
		SDL_Renderer* _winRenderer;
#else
		SDL_Surface* _winSurface;
#endif

		friend class GameManager;

	public:
		/*
		Creates a texture from a given surface
		*/
		SDL_Texture* CreateTexture(SDL_Surface* surface);

	private:
		void Init();

		void FixPositionForRotation(SDL_Surface* _rotatedSurface, Entity* _entity, SurfaceImage* _image);
		void FixPositionForParentRotation(Entity* _entity);

		void RenderEntity(Entity* entity);

#if RENDERING_TYPE == TEXTURE_RENDERING
		void RenderTextureEntity(Entity* _entity, TextureImage* _image);
#else
		void RenderSurfaceEntity(Entity* _entity, SurfaceImage* _image);
#endif

		void RenderScene();
	};
}