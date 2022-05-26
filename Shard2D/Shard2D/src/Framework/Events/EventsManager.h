/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
	private:
		EventsManager();

		~EventsManager();

		friend class Managers;
		friend class GameManager;

		std::vector<std::string> eventsToDispatch;
		std::vector<KeyboardEvent> keyboardEventsToDispatch;
		std::vector<std::string> mouseEventsToDispatch;

		Vector2 mousePosition;

		/**
		Catches all the inputs from the SDL_PollEvent and fill the events lists for the dispatch.
		*/
		void CatchInputs();
		/**
		Dispatch all the catched MouseEvents from the CatchInputs function. The MouseEvents will stop if they find a GameObject capable of getting a mouse event and with blockMouseEvents set to false.
		*/
		void DispatchMouseEvents();
		/**
		Dispatch all the catched KeyboardEvents from the CatchInputs function.
		*/
		void DispatchKeyboardEvents();
		/**
		Checks if the player is pointing to a GameObject with the mouseEvent set to true. A MouseEvent can be called only if the cursor is pointing to the specified GameObject.
		*/
		void CheckEntitiesForMouseEvents(Entity* entity, bool& deadlineReached);
		/**
		Checks the mouse button pressed.
		*/
		void RunMouseButtonDownEvent(SDL_Event& sdlEvent);
		/**
		Checks the mouse button released.
		*/
		void RunMouseButtonUpEvent(SDL_Event& sdlEvent);
		/**
		Checks the mouse wheel movement
		*/
		void RunMouseWheelEvent(SDL_Event& sdlEvent);

	public:
		/**
		Return the actual mouse position.
		@param fixedWithResolution: return the position with the default resolution adaptation (check the SetDefaultResolution in GraphicManager.h)
		*/
		Vector2 GetMousePosition(bool fixedWithResolution);
	};
}