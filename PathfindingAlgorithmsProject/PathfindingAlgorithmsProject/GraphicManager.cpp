#include "GraphicManager.h"
#include <iostream>

GraphicManager::GraphicManager()
{
	window = nullptr;
	winSurface = nullptr;
}

GraphicManager::~GraphicManager()
{
}

bool GraphicManager::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	window = SDL_CreateWindow("MainWIndow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_MAXIMIZED);
	if (!window) 
	{
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	winSurface = SDL_GetWindowSurface(window);
	if (!winSurface) 
	{
		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 0, 0, 0));
	SDL_UpdateWindowSurface(window);
	return true;
}

GameObject* GraphicManager::GetStage() const
{
	return nullptr;
}
