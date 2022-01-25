#include "EventDispatcher.h"

EventListener::EventListener(void(*newCallback)(Event* _event), int newPriority)
	: callback(newCallback), priority(newPriority)
{

}

bool EventListener::Equals(void(*callback)(Event* _event))
{
	return this->callback == callback;
}
