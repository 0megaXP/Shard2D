#pragma once

#include <map>
#include <vector>

template<typename t1, typename t2>
class CustomMap
{
public:
	CustomMap<t1, t2>() {};

private:
	std::map<t1, t2> _map;
	std::map<t1, t2 >::iterator _iterator;

public:
	t2 Get(t1 key)
	{
		_iterator = _map.find(key);
		return _iterator->second;
	}

	void Set(t1 key, t2 valueToSet)
	{
		_iterator = _map.find(key);
		if (_iterator != _map.end())
			_iterator->second = valueToSet;
	}

	void Insert(t1 key, t2 value, bool unique = false)
	{
		if (unique && _map.count(key) > 0)
			return;

		_map.insert(std::pair<t1, t2>(key, value));
	}

	void Remove(t2 value)
	{
		_map.erase(value);
	}

	bool Contains(t1 key)
	{
		return _map.count(key) > 0;
	}

	std::vector<t2> GetAllValues()
	{
		std::vector<t2> v;

		for (_iterator = _map.begin(); _iterator != _map.end(); ++_iterator)
		{
			v.push_back(_iterator->second);
		}

		return v;
	}

	std::map<t1, t2> Map()
	{
		return _map;
	}
};

