#pragma once

#include <vector>
#include <string>
#include <SDL.h>

#include "EventListener.h"

class EventDispatcher;

class EventsManager
{
public:
	EventsManager();

	~EventsManager();

	friend class GameManager;

private:
	std::vector<std::string> eventsToDispatch;
	std::vector<std::string> mouseEventsToDispatch;

	int _actualMouseX = 0;
	int _actualMouseY = 0;

	void CatchInputs();

	void DispatchMouseEvents();

	void CheckMouseOverlapEvents();

	void RunMouseButtonDownEvent(SDL_Event& sdlEvent);

	void RunMouseButtonUpEvent(SDL_Event& sdlEvent);
};

