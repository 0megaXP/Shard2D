#pragma once

#include <string>

#include "Event.h"

class EventDispatcher;

class MouseEvent : virtual public Event
{
public:
	MouseEvent() : Event("") { this->_id = "MouseEvent"; };
	MouseEvent(std::string type) { this->_type = type;  this->_id = "MouseEvent"; };

	static const inline std::string LeftButtonPressed = "leftButtonPressed";

private:
	friend class EventDispatcher;

public:
	virtual std::string GetID() { return this->_id; };
};

