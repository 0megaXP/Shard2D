#pragma once

#include <string>
#include <vector>
#include <memory>

#include "EventListener.h"
#include "../Utils/ShardUtils.h"

namespace Shard2D
{
	class Event;

	class EventDispatcher
	{
	public:
		EventDispatcher() : _target(this) {};
		EventDispatcher(EventDispatcher* target) : _target(target) {};

		~EventDispatcher();

	private:

		friend class EventsManager;

		CustomMap<std::string, std::vector<std::shared_ptr<Listener>>*> _eventMap;
		EventDispatcher* _target;

	public:
		/*
			Registers an event listener object with an EventDispatcher object so that the listener receives notification of an event. You can register event listeners on all nodes in the display list for a
			specific type of event, phase, and priority.

			@param newEventType:	The type of the event.
			@param callback:		The callback function for the EventListener. once the this event type is dispatched, the callback function will be called. It passes the event created.
			@param priority:		The priority level of the EventListener. The priority is designated by a signed 32-bit integer. The higher the number, the higher the priority.
									All listeners with priority n are processed before listeners of priority n-1. If two or more listeners share the same priority, they are processed in the
									order in which they were added. The default priority is 0.

			@throws ArgumentError The callback specified is not a function.
		*/
		template<typename T>
		void AddEventListener(std::string newEventType, void(*callback)(T* _event), int priority = 0);
		/*
			Registers an event listener object with an EventDispatcher object so that the listener receives notification of an event. You can register event listeners on all nodes in the display list for a
			specific type of event, phase, and priority.

			@param newEventType:	The type of the event.
			@param callback:		The callback method for the EventListener. once the this event type is dispatched, the callback method will be called. It passes the event created.
			@param object:			The object containing the method of the callback.
			@param priority:		The priority level of the EventListener. The priority is designated by a signed 32-bit integer. The higher the number, the higher the priority.
									All listeners with priority n are processed before listeners of priority n-1. If two or more listeners share the same priority, they are processed in the
									order in which they were added. The default priority is 0.

			@throws ArgumentError The callback specified is not a function.
		*/
		template<typename T, typename T2>
		void AddEventListener(std::string newEventType, void(T2::*callback)(T* _event), T2* newObject, int priority = 0);

		/**
			Removes a listener from the EventDispatcher object. If there is no matching listener registered with the EventDispatcher object, a call to this method has no effect.

			@param newEventType:	The type of event.
			@param callback:		The callback function for the EventListener.
		**/
		template<typename T>
		void RemoveEventListener(std::string newEventType, void(*callback)(T* _event));
		/**
			Removes a listener from the EventDispatcher object. If there is no matching listener registered with the EventDispatcher object, a call to this method has no effect.

			@param newEventType:	The type of event.
			@param callback:		The callback method for the EventListener.
			@param object:			The object containing the method of the callback.
		**/
		template<typename T, typename T2>
		void RemoveEventListener(std::string newEventType, void(T2::*callback)(T* _event), T2* object);

		void RemoveAllListener();

		/**
			Dispatches an event into the event flow. The event target is the EventDispatcher object upon which the `DispatchEvent()` method is called.

			@param eventType:		The type of event that is dispatched into the event flow.
		**/
		template<typename T>
		void DispatchEvent(std::string eventType);

		/**
			Dispatches an event into the event flow. The event target is the EventDispatcher object upon which the `DispatchEvent()` method is called.

			@param _event:		The event that is dispatched into the event flow.
		**/
		template<typename T>
		void DispatchEvent(T _event);

		/**
			Checks whether the EventDispatcher object has any listeners registered for a specific type of event.

			@param newEventType:	The type of event.
			@param callback:		The callback function for the EventListener.
			@return					A value of `true` if a listener of the specified type is registered; `false` otherwise.
		**/
		template<typename T>
		bool HasEventListener(std::string newEventType, void(*callback)(T* _event));
		/**
			Checks whether the EventDispatcher object has any listeners registered for a specific type of event.

			@param newEventType:	The type of event.
			@param callback:		The callback method for the EventListener.
			@param object:			The object containing the method of the callback.
			@return					A value of `true` if a listener of the specified type is registered; `false` otherwise.
		**/
		template<typename T, typename T2>
		bool HasEventListener(std::string newEventType, void(T2::*callback)(T* _event), T2* object);
	};
}

#include "EventDispatcher.tpp"