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

void EventDispatcher::AddEventListener(std::string newEventType, void(*callback)(Event* _event), int priority)
{
	if (callback == nullptr)
		throw std::invalid_argument("The callback is an invalid memory adress.");

	if (_eventMap.count(newEventType) <= 0)
		_eventMap.insert(std::pair<std::string, std::vector<EventListener*>>(newEventType, std::vector<EventListener*>()));

	EventListener* _eventListener = new EventListener(callback, priority);
	std::map<std::string, std::vector<EventListener*>>::iterator iterator = _eventMap.find(newEventType);
	iterator->second.push_back(_eventListener);
}
