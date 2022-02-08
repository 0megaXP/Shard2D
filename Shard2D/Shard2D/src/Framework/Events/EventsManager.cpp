#include "EventsManager.h"

#include "../GameObjects/GameObject.h"
#include "../Management/Managers.h"

EventsManager::EventsManager()
{
}

EventsManager::~EventsManager()
{
}

void EventsManager::CatchInputs()
{
	SDL_GetMouseState(&_actualMouseX, &_actualMouseY);

	SDL_Event sdlEvent;
	eventsToDispatch.clear();
	mouseEventsToDispatch.clear();

	while (SDL_PollEvent(&sdlEvent) != 0)
	{
		switch (sdlEvent.type)
		{
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				break;
			case SDL_MOUSEBUTTONUP:
				RunMouseButtonUpEvent(sdlEvent);
				break;
			case SDL_MOUSEBUTTONDOWN:
				RunMouseButtonDownEvent(sdlEvent);
				break;
			case SDL_MOUSEWHEEL:
				break;
		}
	}
}

void EventsManager::DispatchMouseEvents()
{
}

void EventsManager::CheckMouseOverlapEvents()
{
	bool deadlineReached = false;
	for (GameObject* object : M_GameObjectsManager->_stagedObjects)
	{
		if (object->mouseEnabled && !deadlineReached)
		{

		}
		else
		{
			object->DispatchEvent<MouseEvent>(MouseEvent::EndOverlap);
		}
	}
}

void EventsManager::RunMouseButtonDownEvent(SDL_Event& sdlEvent)
{
	switch (sdlEvent.button.button)
	{
		case SDL_BUTTON_LEFT:
			mouseEventsToDispatch.push_back(MouseEvent::LeftButtonPressed);
			break;
		case SDL_BUTTON_RIGHT:
			mouseEventsToDispatch.push_back(MouseEvent::RightButtonPressed);
			break;
		case SDL_BUTTON_MIDDLE:
			mouseEventsToDispatch.push_back(MouseEvent::ScrollWheelPressed);
			break;
	}
}

void EventsManager::RunMouseButtonUpEvent(SDL_Event& sdlEvent)
{
	switch (sdlEvent.button.button)
	{
	case SDL_BUTTON_LEFT:
		mouseEventsToDispatch.push_back(MouseEvent::LeftButtonReleased);
		break;
	case SDL_BUTTON_RIGHT:
		mouseEventsToDispatch.push_back(MouseEvent::RightButtonReleased);
		break;
	case SDL_BUTTON_MIDDLE:
		mouseEventsToDispatch.push_back(MouseEvent::ScrollWheelReleased);
		break;
	}
}
