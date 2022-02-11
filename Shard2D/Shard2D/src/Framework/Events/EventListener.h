#pragma once

#include "../Utils/ShardUtils.h"
#include "Event.h"
#include "MouseEvent.h"

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
	EventListener(void (*newCallback)(T* _event), int newPriority = 0) : callback(newCallback), priority(newPriority) { _eventID = T().GetID(); };
	~EventListener() { };

private:
	void (*callback)(T* _event);
	int priority;
	std::string _eventID;

	friend class EventDispatcher;
	friend class EventListener<T>;

public:
	bool Compare(EventListener<T> _eventListener) {	 return callback == _eventListener.callback &&
															_eventID == _eventListener._eventID &&
															priority == _eventListener.priority; };
};