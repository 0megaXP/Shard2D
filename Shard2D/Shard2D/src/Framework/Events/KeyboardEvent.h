#pragma once

#include <string>

#include "Event.h"
#include "Keycode.h"

class EventDispatcher;

class KeyboardEvent : virtual public Event
{
public:
	KeyboardEvent() : Event("") { this->_id = "KeyboardEvent"; };
	KeyboardEvent(std::string type) { this->_type = type;  this->_id = "KeyboardEvent"; };
	KeyboardEvent(std::string type, Shard2D::Keycode newKeycode) : _keycode(newKeycode) { this->_type = type;  this->_id = "KeyboardEvent"; };

	static const inline std::string ButtonPressed = "buttonPressed"; 
	static const inline std::string ButtonReleased = "buttonReleased";

private:
	Shard2D::Keycode _keycode = Shard2D::Keycode::Unknown;

public:
	Shard2D::Keycode GetKeycode() { return _keycode; };
};

