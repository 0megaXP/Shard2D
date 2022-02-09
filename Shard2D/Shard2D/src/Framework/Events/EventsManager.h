#pragma once

#include <vector>
#include <string>
#include <SDL.h>

#include "EventListener.h"

class EventDispatcher;
class GameObject;

class EventsManager
{
public:
	EventsManager();

	~EventsManager();

	friend class GameManager;

private:
	std::vector<std::string> eventsToDispatch;
	std::vector<std::string> mouseEventsToDispatch;

	Vector2 mousePosition;

	void CatchInputs();

	void DispatchMouseEvents();

	void CheckObjectForEvents(GameObject* object, bool &deadlineReached);

	void RunMouseButtonDownEvent(SDL_Event& sdlEvent);

	void RunMouseButtonUpEvent(SDL_Event& sdlEvent);
};

