#include "EventCallback.h"

namespace Shard2D
{
	template<typename T>
	void EventDispatcher::AddEventListener(std::string newEventType, void(*callback)(T* _event), int priority)
	{
		if (callback == nullptr)
			throw std::invalid_argument("The callback is an invalid memory adress.");

		// TODO optimize and improvve the event listener management (maybe not using vector pointers)
		if (!_eventMap.Contains(newEventType))
			_eventMap.Insert(newEventType, new std::vector< std::shared_ptr<Listener>>());

		FunctionEventCallback<T>* temp = new FunctionEventCallback<T>(callback);

		std::shared_ptr<EventListener<T>> _eventListener = std::shared_ptr<EventListener<T>>(new EventListener<T>(temp, priority));
		_eventMap.Get(newEventType)->push_back(_eventListener);
	}

	template<typename T, typename T2>
	void EventDispatcher::AddEventListener(std::string newEventType, void(T2::* callback)(T* _event), T2* newObject, int priority)
	{
		if (callback == nullptr)
			throw std::invalid_argument("The callback is an invalid memory adress.");

		// TODO optimize and improvve the event listener management (maybe not using vector pointers)
		if (!_eventMap.Contains(newEventType))
			_eventMap.Insert(newEventType, new std::vector< std::shared_ptr<Listener>>());

		MethodsEventCallback<T, T2>* temp = new MethodsEventCallback<T, T2>(callback, newObject);

		std::shared_ptr<EventListener<T>> _eventListener = std::shared_ptr<EventListener<T>>(new EventListener<T>(temp, priority));
		_eventMap.Get(newEventType)->push_back(_eventListener);
	}

	template<typename T>
	void EventDispatcher::RemoveEventListener(std::string newEventType, void(*callback)(T* _event))
	{
		if (callback == nullptr)
			return;

		if (!_eventMap.Contains(newEventType))
			return;

		std::vector<std::shared_ptr<Listener>>* listenersVectorPtr = _eventMap.Get(newEventType);
		FunctionEventCallback<T> comparingCallback = FunctionEventCallback<T>(callback);
		for (UINT i = 0; i < listenersVectorPtr->size(); i++)
		{
			EventListener<T>* tempListener = static_cast<EventListener<T>*>(listenersVectorPtr->at(i).get());
			if (tempListener != nullptr &&
				tempListener->_eventID == T(newEventType).GetID() &&
				tempListener->_callback->Compare(&comparingCallback))
			{
				listenersVectorPtr->erase(listenersVectorPtr->begin() + i);
				return;
			}
		}
	}

	template<typename T, typename T2>
	void EventDispatcher::RemoveEventListener(std::string newEventType, void(T2::* callback)(T* _event), T2* object)
	{
		if (callback == nullptr)
			return;

		if (!_eventMap.Contains(newEventType))
			return;

		std::vector<std::shared_ptr<Listener>>* listenersVectorPtr = _eventMap.Get(newEventType);
		MethodsEventCallback<T, T2> comparingCallback = MethodsEventCallback<T, T2>(callback, object);
		for (UINT i = 0; i < listenersVectorPtr->size(); i++)
		{
			EventListener<T>* tempListener = static_cast<EventListener<T>*>(listenersVectorPtr->at(i).get());
			if (tempListener != nullptr &&
				tempListener->_eventID == T(newEventType).GetID() &&
				tempListener->_callback->Compare(&comparingCallback))
			{
				listenersVectorPtr->erase(listenersVectorPtr->begin() + i);
				return;
			}
		}
	}

	template<typename T>
	void EventDispatcher::DispatchEvent(std::string eventType)
	{
		// TODO Priority management
		if (_eventMap.Contains(eventType))
		{
			T* _event = new T(eventType);
			_event->_target = this;

			for (std::shared_ptr<Listener> listener : *_eventMap.Get(eventType))
			{
				EventListener<T>* tempListener = static_cast<EventListener<T>*>(listener.get());
				if (tempListener != nullptr)
				{
					tempListener->_callback->RunCallback(_event);
				}
			}

			delete _event;
		}
	}

	template<typename T>
	void EventDispatcher::DispatchEvent(T _newEvent)
	{
		// TODO Priority management
		if (_eventMap.Contains(_newEvent.GetType()))
		{
			T* _event = new T(_newEvent);
			_event->_target = this;

			for (std::shared_ptr<Listener> listener : *_eventMap.Get(_newEvent.GetType()))
			{
				EventListener<T>* tempListener = static_cast<EventListener<T>*>(listener.get());
				if (tempListener != nullptr)
				{
					tempListener->_callback->RunCallback(_event);
				}
			}

			delete _event;
		}
	}

	template<typename T>
	bool EventDispatcher::HasEventListener(std::string newEventType, void(*callback)(T* _event))
	{
		if (!_eventMap.Contains(newEventType))
			return false;

		FunctionEventCallback<T> comparingCallback = FunctionEventCallback<T>(callback);
		for (std::shared_ptr<Listener> listener : *_eventMap.Get(newEventType))
		{
			EventListener<T>* tempListener = static_cast<EventListener<T>*>(listener.get());
			if (tempListener != nullptr &&
				tempListener->_eventID == T(newEventType).GetID() &&
				tempListener->_callback->Compare(&comparingCallback))
				return true;
		}

		return false;
	}

	template<typename T, typename T2>
	bool EventDispatcher::HasEventListener(std::string newEventType, void(T2::* callback)(T* _event), T2* object)
	{
		if (!_eventMap.Contains(newEventType))
			return false;

		MethodsEventCallback<T, T2> comparingCallback = MethodsEventCallback<T, T2>(callback, object);
		for (std::shared_ptr<Listener> listener : *_eventMap.Get(newEventType))
		{
			EventListener<T>* tempListener = static_cast<EventListener<T>*>(listener.get());
			if (tempListener != nullptr &&
				tempListener->_eventID == T(newEventType).GetID() &&
				tempListener->_callback->Compare(&comparingCallback))
				return true;
		}

		return false;
	}
}