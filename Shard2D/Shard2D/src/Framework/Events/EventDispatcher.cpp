#include "EventDispatcher.h"

#include <stdexcept>

#include "Event.h"

EventListener::EventListener(void(*newCallback)(Event* _event), int newPriority)
	: callback(newCallback), priority(newPriority)
{

}

bool EventListener::Equals(void(*callback)(Event* _event))
{
	return this->callback == callback;
}

EventDispatcher::~EventDispatcher()
{
	// Deallocate all the vector pointers inside the eventMap
	std::vector<std::vector<std::shared_ptr<EventListener>>*> listenerVectors = _eventMap.GetAllValues();
	for (std::vector<std::shared_ptr<EventListener>>* vectorPtr : listenerVectors)
		delete vectorPtr;
}

void EventDispatcher::AddEventListener(std::string newEventType, void(*callback)(Event* _event), int priority)
{
	if (callback == nullptr)
		throw std::invalid_argument("The callback is an invalid memory adress.");

	// TODO optimize and improvve the event listener management (maybe not using vector pointers)
	if (!_eventMap.Contains(newEventType))
		_eventMap.Insert(newEventType, new std::vector< std::shared_ptr<EventListener>>());

	std::shared_ptr<EventListener> _eventListener = std::shared_ptr<EventListener>(new EventListener(callback, priority));
	_eventMap.Get(newEventType)->push_back(_eventListener);
}

void EventDispatcher::DispatchEvent(Event* _event)
{
	// TODO Priority management
	if (_eventMap.Contains(_event->GetType()))
		for (std::shared_ptr<EventListener> listener : *_eventMap.Get(_event->GetType()))
			listener.get()->callback(_event);
}	
		
