#include "./hash_table.h"

template <typename Key, typename Val, typename HeshFunction >
HashTable<Key, Val>::HashTable(size_t cap ,HeshFunction h)
{
	myStr.reserve(455);
	size_t hash_value = hashF(str);
	
	if(_my_set[hash_value] != NULL) { }
	else {
		_my_set[hash_value].push_back[std::make_pair(hash_value, str)]; // kisat
	}
	++_size;
}
/*
template <typename Key, typename Val, typename HeshFunction >
size_t	hashF(const std::string& name, bool halfsize = false)
{
	size_t hash_val = 0;
	for(int i = 0; i < name.size(); ++i)
	{
		hash_val += name[i];
		hash_val = (hash_val * name[i]) % consts::reservedSize;
	}
	return hash_val;
}
*/

template <typename Key, typename Val, typename HeshFunction >
HashTable<Key, Val>::HashTable(HeshFunction h)
			:_hesh{h},_my_set(consts::reservedSize){}
			
