#pragma once

#include <string>

namespace Shard2D
{
	class EventDispatcher;

	class Event
	{
	public:
		Event() : _type(""), _id("Event") {};
		Event(std::string type) : _type(type), _id("Event") {};

		static const inline std::string Added = "added";

		static const inline std::string Removed = "removed";

		static const inline std::string Update = "update";

		static const inline std::string Rendered = "rendered";

	private:
		friend class EventDispatcher;

	protected:
		std::string _type;
		std::string _id;

		EventDispatcher* _target = nullptr;

	public:
		std::string GetType() const;
		EventDispatcher* GetTarget() const;

		virtual std::string GetID() { return _id; };
	};
}