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

#include <string>
#include <SDL.h>

#include "Event.h"

namespace Shard2D
{
	class EventDispatcher;

	class MouseEvent : virtual public Event
	{
	public:
		MouseEvent() : Event("") { this->_id = "MouseEvent"; SDL_GetMouseState(&_mouseX, &_mouseY); };
		MouseEvent(std::string type) { this->_type = type;  this->_id = "MouseEvent"; SDL_GetMouseState(&_mouseX, &_mouseY); };

		static const inline std::string LeftButtonPressed = "leftButtonPressed";
		static const inline std::string LeftButtonReleased = "leftButtonReleased";

		static const inline std::string RightButtonPressed = "rightButtonPressed";
		static const inline std::string RightButtonReleased = "rightButtonReleased";

		static const inline std::string ScrollWheelPressed = "scrollWheelPressed";
		static const inline std::string ScrollWheelReleased = "scrollWheelReleased";

		static const inline std::string ScrollWheelUp = "scrollWheelUp";
		static const inline std::string ScrollWheelDown = "scrollWheelDown";

		static const inline std::string BeginOverlap = "beginOverlap";
		static const inline std::string EndOverlap = "endOverlap";

	private:
		friend class EventDispatcher;

		int _mouseX = 0;

		int _mouseY = 0;

	public:
		virtual std::string GetID() { return this->_id; };

		int GetMouseX() { return _mouseX; };

		int GetMouseY() { return _mouseY; };
	};
}