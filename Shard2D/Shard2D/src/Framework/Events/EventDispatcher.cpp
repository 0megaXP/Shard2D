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
	RemoveAllListener();
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

void EventDispatcher::RemoveEventListener(std::string newEventType, void(*callback)(Event* _event))
{
	if (callback == nullptr)
		return;

	if (!_eventMap.Contains(newEventType))
		return;

	std::vector<std::shared_ptr<EventListener>>* listenersVectorPtr = _eventMap.Get(newEventType);
	if (listenersVectorPtr->size() > 1)
	{
		for (int i = 0; i < listenersVectorPtr->size(); i++)
		{
			if (listenersVectorPtr->at(i).get()->Equals(callback))
			{
				listenersVectorPtr->erase(listenersVectorPtr->begin() + i);
				return;
			}
		}
	}
	else
	{
		if (listenersVectorPtr->at(0).get()->Equals(callback))
		{
			delete(_eventMap.Get(newEventType));
			_eventMap.Remove(newEventType);
		}
	}
}

void EventDispatcher::RemoveAllListener()
{
	// Deallocate all the vector pointers inside the eventMap
	std::vector<std::vector<std::shared_ptr<EventListener>>*> listenerVectors = _eventMap.GetAllValues();
	for (std::vector<std::shared_ptr<EventListener>>* vectorPtr : listenerVectors)
		delete vectorPtr;
	_eventMap.Reset();
}

void EventDispatcher::DispatchEvent(std::string eventType)
{
	// TODO Priority management
	if (_eventMap.Contains(eventType))
	{
		Event* _event = new Event(eventType);
		_event->_target = this;

		for (std::shared_ptr<EventListener> listener : *_eventMap.Get(eventType))
			listener.get()->callback(_event);

		delete _event;
	}
}

bool EventDispatcher::HasEventListener(std::string newEventType, void(*callback)(Event* _event))
{
	if (!_eventMap.Contains(newEventType))
		return false;

	for (std::shared_ptr<EventListener> listener : *_eventMap.Get(newEventType))
		if (listener.get()->callback == callback)
			return true;

	return false;
}

		
