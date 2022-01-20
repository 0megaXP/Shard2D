#pragma once

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
	SDL_Surface* _winSurface;
	SDL_Renderer* _winRenderer;

	friend class GameManager;

public:
	SDL_Texture* CreateTexture(SDL_Surface* surface);

private:
	void Init();

	void FixPositionForRotation(SDL_Surface* _rotatedSurface, GameObject* _object, SurfaceImage* _image);
	void FixPositionForParentRotation(SDL_Surface* _rotatedSurface, GameObject* _object);

	void RenderObject(GameObject* object);
	void RenderSurfaceObject(GameObject* _object, SurfaceImage* _image);

	void RenderScene();
};

