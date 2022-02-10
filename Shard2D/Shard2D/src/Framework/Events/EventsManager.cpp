#include "EventsManager.h"

#include "../Entities/Entity.h"
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
	// If true means that every other overlap with entities will be denied
	bool deadlineReached = false;
	// Checks all the entities from the end
	for (int i = M_EntitiesManager->_stagedEntities.size() - 1; i >= 0; i--)
	{
		Entity* object = M_EntitiesManager->_stagedEntities[i];
		// Checks all the entitiy's children from the end
		if(object->_children.size() > 0)
			for (int childI = object->_children.size() - 1; childI >= 0; childI--)
				CheckEntitiesForMouseEvents(object->_children[childI], deadlineReached);

		CheckEntitiesForMouseEvents(object, deadlineReached);
	}
}

void EventsManager::DispatchKeyboardEvents()
{
	if (keyboardEventsToDispatch.size() > 0)
	{
		for (int i = M_EntitiesManager->_stagedEntities.size() - 1; i >= 0; i--)
		{
			Entity* object = M_EntitiesManager->_stagedEntities[i];
			// Checks all the entitiy's children from the end
			if (object->_children.size() > 0)
				for (int childI = object->_children.size() - 1; childI >= 0; childI--)
					for (KeyboardEvent e : keyboardEventsToDispatch)
						object->_children[childI]->DispatchEvent<KeyboardEvent>(e);

			for (KeyboardEvent e : keyboardEventsToDispatch)
				object->DispatchEvent<KeyboardEvent>(e);
		}
	}
}

void EventsManager::CheckEntitiesForMouseEvents(Entity* entity, bool& deadlineReached)
{
	if (entity->mouseEnabled && !deadlineReached)
	{
		// Checks if the mouse is inside the entity 
		if (PointInsideRect(mousePosition, Vector2(entity->_finalFixedX, entity->_finalFixedY), entity->width * entity->GlobalScaleX(), entity->height * entity->GlobalScaleY(), entity->GlobalRotation()))
		{
			if (!entity->mouseOverlapped)
			{
				entity->mouseOverlapped = true;
				entity->DispatchEvent<MouseEvent>(MouseEvent::BeginOverlap);
			}

			// Dispatch all the others MouseEvents
			for (std::string _event : mouseEventsToDispatch)
				entity->DispatchEvent<MouseEvent>(_event);

			if (entity->blockMouseEvents)
				deadlineReached = true;
		}
		// Cursor outside the entity, call the EndOverlap event
		else
		{
			if (entity->mouseOverlapped)
			{
				entity->mouseOverlapped = false;
				entity->DispatchEvent<MouseEvent>(MouseEvent::EndOverlap);
			}
		}
	}
	// Entity unreachable, call the EndOverlap event
	else
	{
		if (entity->mouseOverlapped)
		{
			entity->mouseOverlapped = false;
			entity->DispatchEvent<MouseEvent>(MouseEvent::EndOverlap);
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
