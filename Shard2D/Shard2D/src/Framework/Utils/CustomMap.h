#pragma once

#include <map>
#include <vector>

template<typename t1, typename t2>
class CustomMap
{
public:
	CustomMap<t1, t2>() : _map(new std::map<t1, t2>()) {}

	~CustomMap<t1, t2>() { _map->clear(); }

private:
	std::map<t1, t2>* _map;
	std::map<t1, t2 >::iterator _iterator;

public:
	/*
	Returns the value at the key given
	*/
	t2 Get(t1 key)
	{
		_iterator = _map->find(key);
		if (_iterator != _map->end())
			return _iterator->second;
		else
			return t2();
	}

	/*
	Overwrites the value at the key given
	*/
	void Set(t1 key, t2 valueToSet)
	{
		_iterator = _map->find(key);
		if (_iterator != _map->end())
			_iterator->second = valueToSet;
	}

	/*
	Creates a new value with the key given
	@param unique: If true, doesn't allow the creation of an existent value
	*/
	void Insert(t1 key, t2 value, bool unique = false)
	{
		if (unique && _map->count(key) > 0)
			return;

		_map->insert(std::pair<t1, t2>(key, value));
	}

	/*
	Removes the value given
	*/
	void Remove(t1 key)
	{
		_iterator = _map->find(key);
		_map->erase(_iterator);
	}

	/*
	Check if the key passed exists in the map
	@return Returns true if the key is found
	*/
	bool Contains(t1 key)
	{
		return _map->count(key) > 0;
	}

	/*
	Returns a vector containing all the map's values	
	*/
	std::vector<t2> GetAllValues()
	{
		std::vector<t2> v;

		for (_iterator = _map->begin(); _iterator != _map->end(); ++_iterator)
		{
			v.push_back(_iterator->second);
		}

		return v;
	}

	/*
	Returns the original map
	*/
	std::map<t1, t2>* Map()
	{
		return _map;
	}

	void Reset()
	{
		_map->clear();
	}
};

