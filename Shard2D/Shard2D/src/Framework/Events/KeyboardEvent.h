#pragma once

#include <string>

#include "Event.h"
#include "Keycode.h"

namespace Shard2D
{
	class EventDispatcher;

	class KeyboardEvent : virtual public Event
	{
	public:
		KeyboardEvent() : Event("") { this->_id = "KeyboardEvent"; };
		KeyboardEvent(std::string type) { this->_type = type;  this->_id = "KeyboardEvent"; };
		KeyboardEvent(std::string type, Keycode::Key newKeycode) : _keycode(newKeycode) { this->_type = type;  this->_id = "KeyboardEvent"; };

		static const inline std::string ButtonPressed = "buttonPressed";
		static const inline std::string ButtonReleased = "buttonReleased";

	private:
		Keycode::Key _keycode = Keycode::Unknown;

	public:
		Keycode::Key GetKeycode() { return _keycode; };
	};
}
