template<typename T>
void EventDispatcher::AddEventListener(std::string newEventType, void(*callback)(T* _event), int priority)
{
	if (callback == nullptr)
		throw std::invalid_argument("The callback is an invalid memory adress.");

	// TODO optimize and improvve the event listener management (maybe not using vector pointers)
	if (!_eventMap.Contains(newEventType))
		_eventMap.Insert(newEventType, new std::vector< std::shared_ptr<Listener>>());

	std::shared_ptr<EventListener<T>> _eventListener = std::shared_ptr<EventListener<T>>(new EventListener<T>(callback, priority));
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
	if (listenersVectorPtr->size() > 1)
	{
		for (UINT i = 0; i < listenersVectorPtr->size(); i++)
		{
			EventListener<T>* tempListener = static_cast<EventListener<T>*>(listenersVectorPtr->at(i).get());
			if (tempListener != nullptr && tempListener->Compare(EventListener<T>(callback)))
			{
				listenersVectorPtr->erase(listenersVectorPtr->begin() + i);
				return;
			}
		}
	}
	else
	{
		EventListener<T>* tempListener = static_cast<EventListener<T>*>(listenersVectorPtr->at(0).get());
		if (tempListener != nullptr && tempListener->Compare(EventListener<T>(callback)))
		{
			delete(_eventMap.Get(newEventType));
			_eventMap.Remove(newEventType);
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
			if (tempListener != nullptr && tempListener->Compare(EventListener<T>(tempListener->callback)))
				tempListener->callback(_event);
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
			if (tempListener != nullptr && tempListener->Compare(EventListener<T>(tempListener->callback)))
				tempListener->callback(_event);
		}

		delete _event;
	}
}

template<typename T>
bool EventDispatcher::HasEventListener(std::string newEventType, void(*callback)(T* _event))
{
	if (!_eventMap.Contains(newEventType))
		return false;

	for (std::shared_ptr<Listener> listener : *_eventMap.Get(newEventType))
	{
		EventListener<T>* tempListener = static_cast<EventListener<T>*>(listener.get());
		if (tempListener != nullptr && tempListener->Compare(EventListener<T>(callback)))
			return true;
	}

	return false;
}