#pragma once

#define SURFACE_RENDERING 0
#define TEXTURE_RENDERING 1

// Must be SURFACE_RENDERING or TEXTURE_RENDERING
#define RENDERING_TYPE TEXTURE_RENDERING

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

struct Image;
struct SurfaceImage;
struct TextureImage;
class GameObject;

class GraphicManager
{
public:
	GraphicManager();
	~GraphicManager();

	SDL_Window* _window;
#if RENDERING_TYPE == TEXTURE_RENDERING
	SDL_Renderer* _winRenderer;
#else
	SDL_Surface* _winSurface;
#endif

	int renderingType = TEXTURE_RENDERING;

	friend class GameManager;

public:
	/*
	Creates a texture from a given surface
	*/
	SDL_Texture* CreateTexture(SDL_Surface* surface);

private:
	void Init();

	void FixPositionForRotation(SDL_Surface* _rotatedSurface, GameObject* _object, SurfaceImage* _image);
	void FixPositionForParentRotation(GameObject* _object);

	void RenderObject(GameObject* object);

#if RENDERING_TYPE == TEXTURE_RENDERING
	void RenderTextureObject(GameObject* _object, TextureImage* _image);
#else
	void RenderSurfaceObject(GameObject* _object, SurfaceImage* _image);
#endif

	void RenderScene();
};

