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

	class TweenEvent : virtual public Event
	{
	public:
		TweenEvent() : Event("") { this->_id = "TweenEvent"; };
		TweenEvent(std::string type) { this->_type = type;  this->_id = "TweenEvent"; };

		static const inline std::string OnComplete = "onComplete";
		static const inline std::string OnRepeat = "onRepeat";
		static const inline std::string OnResume = "onResume";
		static const inline std::string OnPause = "onPause";

	private:
		friend class EventDispatcher;

	public:
		virtual std::string GetID() { return this->_id; };
	};
}