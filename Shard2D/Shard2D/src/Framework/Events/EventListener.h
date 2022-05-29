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

#include "EventTypes/Event.h"
#include "EventTypes/MouseEvent.h"
#include "EventCallback.h"
#include "../ShardUtils.h"

namespace Shard2D
{
	class Listener
	{
	public:
		Listener() {};
		~Listener() {};

	protected:
		friend class EventDispatcher;
	};

	template<typename T>
	class EventListener : public Listener
	{
	public:
		EventListener(EventCallback<T>* newCallback, int newPriority = 0) : _callback(newCallback), priority(newPriority) { _eventID = T().GetID(); };
		~EventListener() { delete _callback; };

	private:
		EventCallback<T>* _callback;
		int priority;
		std::string _eventID;

		friend class EventDispatcher;
		friend class EventListener<T>;

	/*public:
		bool Compare(EventListener<T> _eventListener) {	 return _callback->Compare(_eventListener._callback) &&
																_eventID == _eventListener._eventID &&
																priority == _eventListener.priority; };*/
	};
}