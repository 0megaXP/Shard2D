#pragma once

#include <string>
#include <map>
#include <vector>

class Event;

class EventListener
{
public:
	EventListener(void (*callback)(Event* _event), int priority = 0);

	void (*callback)(Event* _event);
	int priority;

	bool Equals(void (*callback)(Event* _event));
};

class EventDispatcher
{
public:
	EventDispatcher() : _target(this) {};
	EventDispatcher(EventDispatcher* target) : _target(target) {};

private:

	std::map<std::string, std::vector<EventListener*>> _eventMap;
	EventDispatcher* _target;

public:
	/*
		Registers an event listener object with an EventDispatcher object so that the listener receives notification of an event. You can register event listeners on all nodes in the display list for a 
		specific type of event, phase, and priority.

		@param newEventType:	The type of the event.
		@param callback:		The callback function for the EventListener. once the this event type is dispatched, the callback function will be called. It passes the event created.
		@param priority:		The priority level of the EventListener. The priority is designated by a signed 32-bit integer. The higher the number, the higher the priority. 
								All listeners with priority n are processed before listeners of priority n-1. If two or more listeners share the same priority, they are processed in the 
								order in which they were added. The default priority is 0.

		@throws ArgumentError The callback specified is not a function.
	*/
	void AddEventListener(std::string newEventType, void(*callback)(Event* _event), int priority = 0);

	void RemoveEventListener(/*EventType type, T listener*/);

	void RemoveAllListener();

	void DispatchEvent(/*Event event*/);

	bool HasEventListener(/*Event event*/) const;
};

