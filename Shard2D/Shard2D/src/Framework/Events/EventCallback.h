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
		typedef void (*FuncPtr)(T* _event);

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
		typedef void (T2::* MetPtr)(T* _event);

		MethodsEventCallback(MetPtr newCallback) : _callback(newCallback) { };

	private:

		MetPtr _callback;

	public:

		bool Compare(EventCallback<T>* otherCallback) override
		{
			MethodsEventCallback<T, T2>* tempCallback = static_cast<MethodsEventCallback<T, T2>*>(otherCallback);
			return tempCallback != nullptr && tempCallback->_callback == _callback;
		}

		void RunCallback(T* _event) override
		{
			_callback(_event);
		}
	};
}