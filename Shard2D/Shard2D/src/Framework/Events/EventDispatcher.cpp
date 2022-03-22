#include "EventDispatcher.h"

#include <stdexcept>

#include "EventTypes/Event.h"
#include "EventTypes/MouseEvent.h"
#include "EventTypes/KeyboardEvent.h"

namespace Shard2D
{
	EventDispatcher::~EventDispatcher()
	{
		RemoveAllListener();
	}

	void EventDispatcher::RemoveAllListener()
	{
		// Deallocate all the vector pointers inside the eventMap
		std::vector<std::vector<std::shared_ptr<Listener>>*> listenerVectors = _eventMap.GetAllValues();
		for (std::vector<std::shared_ptr<Listener>>* vectorPtr : listenerVectors)
			delete vectorPtr;
		_eventMap.Reset();
	}
}