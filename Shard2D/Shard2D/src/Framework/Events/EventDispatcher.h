#pragma once

#include <string>


#include <vector>
#include <memory>

#include "../Utils/ShardUtils.h"

class Event;

class EventListener
{
public:
	EventListener(void (*callback)(Event* _event), int priority = 0);
	~EventListener() { Log("EventListener destroyed", TextColor::Purple); };

private:
	void (*callback)(Event* _event);
	int priority;

	friend class EventDispatcher;

public:
	bool Equals(void (*callback)(Event* _event));
};

class EventDispatcher
{
public:
	EventDispatcher() : _target(this) {};
	EventDispatcher(EventDispatcher* target) : _target(target) {};

	~EventDispatcher();

private:

	CustomMap<std::string, std::vector<std::shared_ptr<EventListener>>*> _eventMap;
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

	/**
		Removes a listener from the EventDispatcher object. If there is no
		matching listener registered with the EventDispatcher object, a call to
		this method has no effect.

		@param newEventType:	The type of event.
		@param callback:		The callback function for the EventListener.
	**/
	void RemoveEventListener(std::string newEventType, void(*callback)(Event* _event));

	void RemoveAllListener();

	/**
		Dispatches an event into the event flow. The event target is the EventDispatcher object upon which the `DispatchEvent()` method is called.

		@param eventType:		The type of event that is dispatched into the event flow.
	**/
	void DispatchEvent(std::string eventType);

	/**
		Checks whether the EventDispatcher object has any listeners registered for a specific type of event.

		@param newEventType:	The type of event.
		@param callback:		The callback function for the EventListener.
		@return					A value of `true` if a listener of the specified type is registered; `false` otherwise.
	**/
	bool HasEventListener(std::string newEventType, void(*callback)(Event* _event));
};

