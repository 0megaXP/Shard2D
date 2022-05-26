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

#include <map>
#include <vector>

namespace Shard2D
{
	template<typename T1, typename T2>
	class CustomMap
	{
	public:
		CustomMap<T1, T2>() : _map(new std::map<T1, T2>()) {}

		~CustomMap<T1, T2>() { _map->clear(); }

	private:
		std::map<T1, T2>* _map;
		std::map<T1, T2 >::iterator _iterator;

	public:
		/*
		Returns the value at the key given
		*/
		T2 Get(T1 key);

		/*
		Overwrites the value at the key given
		*/
		void Set(T1 key, T2 valueToSet);

		/*
		Creates a new value with the key given
		@param unique: If true, doesn't allow the creation of an existent value
		*/
		void Insert(T1 key, T2 value, bool unique = false);

		/*
		Removes the value given
		*/
		void Remove(T1 key);

		/*
		Check if the key passed exists in the map
		@return Returns true if the key is found
		*/
		bool Contains(T1 key);

		/*
		Returns a vector containing all the map's values
		*/
		std::vector<T2> GetAllValues();

		/*
		Returns the original map
		*/
		std::map<T1, T2>* Map();

		void Reset();
	};
}

#include "CustomMap.tpp"