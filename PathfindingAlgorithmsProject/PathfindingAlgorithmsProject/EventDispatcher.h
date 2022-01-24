#pragma once
class EventDispatcher
{
public:
	void AddEventListener(/*EventType type, T listener, int priority*/);

	void RemoveEventListener(/*EventType type, T listener*/);

	void RemoveAllListener();

	void DispatchEvent(/*Event event*/);

	bool HasEventListener(/*Event event*/) const;
};

