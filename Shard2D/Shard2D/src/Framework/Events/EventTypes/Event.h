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