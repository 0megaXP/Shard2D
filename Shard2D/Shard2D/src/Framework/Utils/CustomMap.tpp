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

namespace Shard2D
{
	template<typename T1, typename T2>
	T2 CustomMap<T1, T2>::Get(T1 key)
	{
		_iterator = _map->find(key);
		if (_iterator != _map->end())
			return _iterator->second;
		else
			return T2();
	}

	template<typename T1, typename T2>
	void CustomMap<T1, T2>::Set(T1 key, T2 valueToSet)
	{
		_iterator = _map->find(key);
		if (_iterator != _map->end())
			_iterator->second = valueToSet;
	}

	template<typename T1, typename T2>
	void CustomMap<T1, T2>::Insert(T1 key, T2 value, bool unique)
	{
		if (unique && _map->count(key) > 0)
			return;

		_map->insert(std::pair<T1, T2>(key, value));
	}

	template<typename T1, typename T2>
	void CustomMap<T1, T2>::Remove(T1 key)
	{
		_iterator = _map->find(key);
		_map->erase(_iterator);
	}

	template<typename T1, typename T2>
	bool CustomMap<T1, T2>::Contains(T1 key)
	{
		return _map->count(key) > 0;
	}

	template<typename T1, typename T2>
	std::vector<T2> CustomMap<T1, T2>::GetAllValues()
	{
		std::vector<T2> v;

		for (_iterator = _map->begin(); _iterator != _map->end(); ++_iterator)
		{
			v.push_back(_iterator->second);
		}

		return v;
	}

	template<typename T1, typename T2>
	std::map<T1, T2>* CustomMap<T1, T2>::Map()
	{
		return _map;
	}

	template<typename T1, typename T2>
	void CustomMap<T1, T2>::Reset()
	{
		_map->clear();
	}
}