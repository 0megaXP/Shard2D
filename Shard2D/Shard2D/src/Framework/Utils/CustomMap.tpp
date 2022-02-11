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