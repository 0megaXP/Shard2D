#pragma once

#include <string>

class EventDispatcher;

class Event
{
public:
	Event() : _type("") {} ;
	Event(std::string type) : _type(type) {};

	static const inline std::string Added = "added";

	static const inline std::string Removed = "removed";

	static const inline std::string Update = "update";

	static const inline std::string Rendered = "rendered";

private:

	friend class EventDispatcher;

protected:
	std::string _type;

	EventDispatcher* _target = nullptr;

public:
	std::string GetType() const;
	EventDispatcher* GetTarget() const;
};