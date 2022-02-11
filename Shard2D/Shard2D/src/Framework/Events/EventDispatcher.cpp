#include "EventDispatcher.h"

#include <stdexcept>

#include "Event.h"
#include "MouseEvent.h"
#include "KeyboardEvent.h"

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