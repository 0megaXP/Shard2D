#pragma once

#include <vector>
#include <string>
#include <SDL.h>

#include "EventListener.h"


namespace Shard2D
{
	class EventDispatcher;
	class Entity;
	class KeyboardEvent;

	class EventsManager
	{
	public:
		EventsManager();

		~EventsManager();

		friend class GameManager;

	private:
		std::vector<std::string> eventsToDispatch;
		std::vector<KeyboardEvent> keyboardEventsToDispatch;
		std::vector<std::string> mouseEventsToDispatch;

		Vector2 mousePosition;

		/**
		Catches all the inputs from the SDL_PollEvent and fill the events lists for the dispatch
		*/
		void CatchInputs();
		/**
		Dispatch all the catched MouseEvents from the CatchInputs function. The MouseEvents will stop if they find a GameObject capable of getting a mouse event and with blockMouseEvents set to false
		*/
		void DispatchMouseEvents();
		/**
		Dispatch all the catched KeyboardEvents from the CatchInputs function
		*/
		void DispatchKeyboardEvents();
		/**
		Checks if the player is pointing to a GameObject with the mouseEvent set to true. A MouseEvent can be called only if the cursor is pointing to the specified GameObject.
		*/
		void CheckEntitiesForMouseEvents(Entity* entity, bool& deadlineReached);
		/**
		Checks the mouse button pressed
		*/
		void RunMouseButtonDownEvent(SDL_Event& sdlEvent);
		/**
		Checks the mouse button released
		*/
		void RunMouseButtonUpEvent(SDL_Event& sdlEvent);
		/**
		Checks the mouse wheel movement
		*/
		void RunMouseWheelEvent(SDL_Event& sdlEvent);
	};
}