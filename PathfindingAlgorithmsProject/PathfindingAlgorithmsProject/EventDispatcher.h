#pragma once

class Event;

class EventListener
{
public:
	EventListener(void (*callback)(Event* _event), int priority);

	void (*callback)(Event* _event);
	int priority;

	bool Equals(void (*callback)(Event* _event));
};

class EventDispatcher
{
public:
	void AddEventListener(/*EventType type, T listener, int priority*/);

	void RemoveEventListener(/*EventType type, T listener*/);

	void RemoveAllListener();

	void DispatchEvent(/*Event event*/);

	bool HasEventListener(/*Event event*/) const;
};

