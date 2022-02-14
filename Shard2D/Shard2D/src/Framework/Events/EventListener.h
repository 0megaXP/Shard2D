#pragma once

#include "../Utils/ShardUtils.h"
#include "Event.h"
#include "MouseEvent.h"
#include "Callback.h"

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
		EventListener(CallbackBase newCallback, int newPriority = 0) : _callback(newCallback), priority(newPriority) { _eventID = T().GetID(); };
		~EventListener() { };

	private:
		CallbackBase _callback;
		int priority;
		std::string _eventID;

		friend class EventDispatcher;
		friend class EventListener<T>;

	public:
		bool Compare(EventListener<T> _eventListener) {	 return _callback.Compare(&_eventListener._callback) &&
																_eventID == _eventListener._eventID &&
																priority == _eventListener.priority; };
	};
}