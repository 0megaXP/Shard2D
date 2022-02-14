#pragma once

namespace Shard2D
{
	enum class CallbackType
	{
		Void,
		Class,
		Param,
		Full
	};

	class CallbackBase
	{
	public:

		friend class EventDispatcher;

		CallbackType type;

		virtual bool Compare(CallbackBase* otherCallback) { return false; };
	};

	class VoidCallback : public CallbackBase
	{
	public:
		typedef void (*FuncPtr)();

		VoidCallback(FuncPtr newCallback) : _callback(newCallback) { this->type = CallbackType::Void; };

	private:

		FuncPtr _callback;

	public:

		bool Compare(CallbackBase* otherCallback) override
		{
			VoidCallback* tempCallback = static_cast<VoidCallback*>(otherCallback);
			return tempCallback != nullptr && tempCallback->_callback == _callback;
		}
	};

	template<typename T>
	class ClassCallback : public CallbackBase
	{
	public:
		typedef void (T::* FuncPtr)();

		ClassCallback(FuncPtr newCallback) : _callback(newCallback) { this->type = CallbackType::Class; };

	private:

		FuncPtr _callback;

	public:

		bool Compare(CallbackBase* otherCallback) override
		{
			ClassCallback<T>* tempCallback = static_cast<ClassCallback<T>*>(otherCallback);
			return tempCallback != nullptr && tempCallback->_callback == _callback;
		}
	};

	template<typename T>
	class ParamCallback : public CallbackBase
	{
	public:
		friend class EventDispatcher;

		typedef void (*FuncPtr)(T* param);

		ParamCallback(FuncPtr newCallback) : _callback(newCallback) { this->type = CallbackType::Param; };

	private:

		FuncPtr _callback;

	public:

		bool Compare(CallbackBase* otherCallback) override
		{
			ParamCallback<T>* tempCallback = static_cast<ParamCallback<T>*>(otherCallback);
			return tempCallback != nullptr && tempCallback->_callback == _callback;
		}
	};

	template<typename T, typename T2>
	class FullCallback : public CallbackBase
	{
	public:
		typedef void (T::* FuncPtr)(T2* param);

		FullCallback(FuncPtr newCallback) : _callback(newCallback) { this->type = CallbackType::Full; };

	private:

		FuncPtr _callback;

	public:

		bool Compare(CallbackBase* otherCallback) override
		{
			FullCallback<T, T2>* tempCallback = static_cast<FullCallback<T, T2>*>(otherCallback);
			return tempCallback != nullptr && tempCallback->_callback == _callback;
		}
	};
}