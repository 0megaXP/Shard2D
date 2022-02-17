#pragma once

namespace Shard2D
{
	template<typename T>
	class EventCallback
	{
	public:

		friend class EventDispatcher;

		virtual bool Compare(EventCallback<T>* otherCallback) { return false; };

		virtual void RunCallback(T* _event) {};
	};

	template<typename T>
	class FunctionEventCallback : public EventCallback<T>
	{
	public:
		typedef void (*FuncPtr)(T*);

		FunctionEventCallback(FuncPtr newCallback) : _callback(newCallback) { };

	private:

		FuncPtr _callback;

	public:

		bool Compare(EventCallback<T>* otherCallback) override
		{
			FunctionEventCallback<T>* tempCallback = static_cast<FunctionEventCallback<T>*>(otherCallback);
			return tempCallback != nullptr && tempCallback->_callback == _callback;
		}

		void RunCallback(T* _event) override
		{
			_callback(_event);
		}
	};

	template<typename T, typename T2>
	class MethodsEventCallback : public EventCallback<T>
	{
	public:
		//typedef void (T2::* MetPtr)(T*);

		MethodsEventCallback(void (T2::* newCallback)(T*), T2* newObject) : _callback(newCallback), _object(newObject) { };

	private:

		T2* _object;

		void (T2::* _callback)(T*);

	public:

		bool Compare(EventCallback<T>* otherCallback) override
		{
			MethodsEventCallback<T, T2>* tempCallback = static_cast<MethodsEventCallback<T, T2>*>(otherCallback);
			return tempCallback != nullptr && tempCallback->_callback == _callback && tempCallback->_object == _object;
		}

		void RunCallback(T* _event) override
		{
			if (_object != nullptr)
			{
				(_object->*_callback) (_event);
			}
			else
			{
				throw std::invalid_argument("The object of the method is null.");
			}
		}
	};
}