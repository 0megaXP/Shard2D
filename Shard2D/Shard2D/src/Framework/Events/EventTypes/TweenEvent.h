#pragma once

#include <string>
#include <SDL.h>

#include "Event.h"

namespace Shard2D
{
	class EventDispatcher;

	class TweenEvent : virtual public Event
	{
	public:
		TweenEvent() : Event("") { this->_id = "TweenEvent"; };
		TweenEvent(std::string type) { this->_type = type;  this->_id = "TweenEvent"; };

		static const inline std::string OnComplete = "onComplete";
		static const inline std::string OnRepeat = "onRepeat";
		static const inline std::string OnResume = "onResume";
		static const inline std::string OnPause = "onPause";

	private:
		friend class EventDispatcher;

	public:
		virtual std::string GetID() { return this->_id; };
	};
}