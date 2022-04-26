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

	class GraphicManager
	{
	private:
		GraphicManager();
		~GraphicManager();

		friend class Managers;

		SDL_Window* _window;

		SDL_Renderer* _winRenderer;

		friend class GameManager;

	public:
		/*
		Creates a texture from a given surface
		*/
		SDL_Texture* CreateTexture(SDL_Surface* surface);

	private:
		void Init();

		void FixPositionForParentRotation(Entity* _entity);

		void RenderEntity(Entity* entity);

		void RenderTextureEntity(Entity* _entity, Image* _image);

		void RenderScene();
	};
}