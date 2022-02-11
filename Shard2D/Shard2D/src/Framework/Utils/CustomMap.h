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