#include "EventsManager.h"

#include "../GameObjects/GameObject.h"
#include "../Management/Managers.h"
#include "../Utils/ShardUtils.h"

#include "KeyboardEvent.h"
#include "Keycode.h"

import MathUtils;

EventsManager::EventsManager()
{
}

EventsManager::~EventsManager()
{
}

void EventsManager::CatchInputs()
{
	// Getting mouse position
	int _actualMouseX = 0;
	int _actualMouseY = 0;
	SDL_GetMouseState(&_actualMouseX, &_actualMouseY);
	mousePosition = Vector2(_actualMouseX, _actualMouseY);

	// Setup the arrays
	eventsToDispatch.clear();
	mouseEventsToDispatch.clear();
	keyboardEventsToDispatch.clear();

	SDL_Event sdlEvent;
	// Loop all the events catched
	while (SDL_PollEvent(&sdlEvent) != 0)
	{
		switch (sdlEvent.type)
		{
			case SDL_KEYDOWN:
				keyboardEventsToDispatch.push_back(KeyboardEvent(KeyboardEvent::ButtonPressed, static_cast<Shard2D::Keycode>(sdlEvent.key.keysym.sym)));
				break;
			case SDL_KEYUP:
				keyboardEventsToDispatch.push_back(KeyboardEvent(KeyboardEvent::ButtonReleased, static_cast<Shard2D::Keycode>(sdlEvent.key.keysym.sym)));
				break;
			case SDL_MOUSEBUTTONUP:
				RunMouseButtonUpEvent(sdlEvent);
				break;
			case SDL_MOUSEBUTTONDOWN:
				RunMouseButtonDownEvent(sdlEvent);
				break;
			case SDL_MOUSEWHEEL:
				RunMouseWheelEvent(sdlEvent);
				break;
			case SDL_QUIT:
				Managers::gameManager->ExitGame();
		}
	}

	DispatchKeyboardEvents();
	DispatchMouseEvents();
}

void EventsManager::DispatchMouseEvents()
{
	// If true means that every other overlap with objects will be denied
	bool deadlineReached = false;
	// Checks all the gameObjects from the end
	for (int i = M_GameObjectsManager->_stagedObjects.size() - 1; i >= 0; i--)
	{
		GameObject* object = M_GameObjectsManager->_stagedObjects[i];
		// Checks all the gameObject's children from the end
		if(object->_children.size() > 0)
			for (int childI = object->_children.size() - 1; childI >= 0; childI--)
				CheckObjectForMouseEvents(object->_children[childI], deadlineReached);

		CheckObjectForMouseEvents(object, deadlineReached);
	}
}

void EventsManager::DispatchKeyboardEvents()
{
	for (int i = M_GameObjectsManager->_stagedObjects.size() - 1; i >= 0; i--)
	{
		GameObject* object = M_GameObjectsManager->_stagedObjects[i];
		// Checks all the gameObject's children from the end
		if (object->_children.size() > 0)
			for (int childI = object->_children.size() - 1; childI >= 0; childI--)
				for(KeyboardEvent e : keyboardEventsToDispatch)
					object->_children[childI]->DispatchEvent<KeyboardEvent>(e);

		for (KeyboardEvent e : keyboardEventsToDispatch)
			object->DispatchEvent<KeyboardEvent>(e);
	}
}

void EventsManager::CheckObjectForMouseEvents(GameObject* object, bool& deadlineReached)
{
	if (object->mouseEnabled && !deadlineReached)
	{
		// Checks if the mouse is inside the object 
		if (PointInsideRect(mousePosition, Vector2(object->_finalFixedX, object->_finalFixedY), object->width * object->GlobalScaleX(), object->height * object->GlobalScaleY(), object->GlobalRotation()))
		{
			if (!object->mouseOverlapped)
			{
				object->mouseOverlapped = true;
				object->DispatchEvent<MouseEvent>(MouseEvent::BeginOverlap);
			}

			// Dispatch all the others MouseEvents
			for (std::string _event : mouseEventsToDispatch)
				object->DispatchEvent<MouseEvent>(_event);

			if (object->blockMouseEvents)
				deadlineReached = true;
		}
		else
		{
			if (object->mouseOverlapped)
			{
				object->mouseOverlapped = false;
				object->DispatchEvent<MouseEvent>(MouseEvent::EndOverlap);
			}
		}
	}
	else
	{
		if (object->mouseOverlapped)
		{
			object->mouseOverlapped = false;
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

void EventsManager::RunMouseWheelEvent(SDL_Event& sdlEvent)
{
	if (sdlEvent.wheel.y > 0)
	{
		mouseEventsToDispatch.push_back(MouseEvent::ScrollWheelUp);
	}
	else if (sdlEvent.wheel.y < 0)
	{
		mouseEventsToDispatch.push_back(MouseEvent::ScrollWheelDown);
	}
}
