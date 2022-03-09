#ifndef HASH_TABLE
#define HASH_TABLE


#include "../Forward_list/forward_list.h"
#include "../String/String.h"
#include "../Vector/vector.h"
#include "../PQueue/PQueue.h"

#include <functional>

namespace consts {
	const int maxSize = 256;
	const size_t reservedSize = 4000; // vec_size
}

template <typename Key, typename Val>
struct pair
{
	Key first{};
	Val second{};
	pair(const Key& k, const Val& v)
		: first{ k }, second{ v }
	{}
	pair()= default;
	pair(const pair&)=default;
	pair& operator=(const pair&)=default;
	pair(pair&&) = delete;
	bool operator<(const pair& other)const
	{
		if (first == other.first)
		{
			return second < other.second;
		}
		return first < other.first;
	}
	bool operator>(const pair& other)const
	{
		if (first == other.first)
		{
			return second > other.second;
		}
		return first > other.first;
	}
	bool operator==(const pair& other)const
	{
		return ( first == other.first && second == other.second );
	}
};


template <typename Key>
size_t Hash(const Key& k, size_t size = consts::reservedSize)
{
	size_t hash_val = 0;
	for(int i = 0; i < k.size(); ++i)
	{		
		hash_val += k[i];
		hash_val *= k[i] % size;
	}
	return hash_val % size;
}

template <typename Key, typename Val, typename HeshFunction = std::function<size_t(const Key&, size_t) >>
class HashTable
{
private:
	Vector< Forward_list< pair< Key, Val > > > _set;
	HeshFunction _Hesh;
	size_t _size;
public:
	HashTable(HeshFunction h = Hash<Key>);
	explicit HashTable(size_t cap, HeshFunction h = Hash<Key>);
	virtual ~HashTable() = default;
	Val& operator[](const Key&);
	Val& find(const Key&);
	void erase(const Key&);
public:
	bool insert(const Key& , const Val&);
	size_t bucket_count();
	size_t bucket_size();
};

#include "./hash_table.hpp"
#endif // HASH_TABLE
