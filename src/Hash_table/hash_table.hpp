#include "./hash_table.h"

template < typename Key, typename Val, typename HeshFunction >
HashTable<Key, Val, HeshFunction>::HashTable(size_t cap, HeshFunction h)
	:_set{ consts::reservedSize, Key() }
{
	_set.resize(cap,Forward_list<pair<Key,Val>>());
	_Hesh = h;
	_size = consts::reservedSize;

}

template <typename Key, typename Val, typename HeshFunction >
HashTable<Key, Val, HeshFunction>::HashTable(HeshFunction h)
{
	_set.resize(consts::reservedSize, Forward_list<pair<Key,Val>>());
	_Hesh = h;
	_size = consts::reservedSize;
}

template <typename Key, typename Val, typename HeshFunction >
bool HashTable<Key, Val, HeshFunction>::insert(const Key& k , const Val& v)
{
	pair <Key,Val>p(k,v);
	_set[_Hesh(k,_size)].push_back(p);
	return true;
}

template <typename Key, typename Val, typename HeshFunction >
size_t HashTable<Key, Val, HeshFunction>::bucket_count()
{
	return _size;
}

template <typename Key, typename Val, typename HeshFunction >
size_t HashTable<Key, Val, HeshFunction>::bucket_size()
{
	size_t count{};
	for (int i = 0 ; i < _size ; ++i)
	{
		if (!_set.isEmpty()){count++;}
	}
	return count;
}

template <typename Key, typename Val, typename HeshFunction >
Val& HashTable<Key, Val, HeshFunction>::operator[](const Key& k)
{
	typename Forward_list<pair<Key,Val>>::iterator it =_set[_Hesh(k,_size)].begin();
	typename Forward_list<pair<Key,Val>>::iterator it_end =_set[_Hesh(k,_size)].end();
	while (it != it_end)
	{
		if ((*it).first == k)
		{
			return (*it).second;
		}
		it++;
	}
	pair<Key,Val> p;
	p.first = k;
	_set[_Hesh(k,_size)].push_front(p);
	it = _set[_Hesh(k,_size)].begin();
	return (*it).second;
}

template <typename Key, typename Val, typename HeshFunction >
Val& HashTable<Key, Val, HeshFunction>::find(const Key& k)
{
	typename Forward_list<pair<Key,Val>>::iterator it =_set[_Hesh(k,_size)].begin();
	typename Forward_list<pair<Key,Val>>::iterator it_end =_set[_Hesh(k,_size)].end();
	while (it != it_end)
	{
		if ((*it).first == k)
		{
			return (*it).second;
		}
		it++;
	}
	throw std::out_of_range("Key is not found.");
}

template <typename Key, typename Val, typename HeshFunction >
void HashTable<Key, Val, HeshFunction>::erase(const Key& k)
{
	typename Forward_list<pair<Key,Val>>::iterator it =_set[_Hesh(k,_size)].begin();
	typename Forward_list<pair<Key,Val>>::iterator it_end =_set[_Hesh(k,_size)].end();
	while (it != it_end)
	{
		if ((*it).first == k)
		{
			_set[_Hesh(k,_size)].removeAt(std::distance( _set[_Hesh(k,_size)].begin(),it));
			return;
		}
		it++;
	}
}
