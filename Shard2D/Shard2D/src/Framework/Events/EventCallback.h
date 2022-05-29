/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <stdexcept>

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