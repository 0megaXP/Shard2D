#pragma once

#include <string>

#include "Event.h"

class EventDispatcher;

class MouseEvent : public Event
{
public:
	static const inline std::string LeftButtonPressed = "leftButtonPressed";

private:
	friend class EventDispatcher;
};

