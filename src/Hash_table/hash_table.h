#ifndef HASH_TABLE
# define HASH_TABLE

#include "../Forward_list/forward_list.h"
#include "../String_source/String.h"
#include "../Vector/Vector.h"


#include <utility>

namespace consts {
	const int MaxSize = 256;
	const size_t reservedSize = 4000; // vec_size
}
template <typename Key>
struct Hesh
{
	size_t operator()(const Key& k)
	{
		size_t hash_val = 0;
		for(int i = 0; i < name.size(); ++i)
		{		
			hash_val += name[i];
			hash_val = (hash_val * name[i]) % consts::reservedSize;
		}
		return hash_val;
	}
}

template <typename Key, typename Val, typename HeshFunction = Hesh<key> >
class HashTable{
	/* containers to store data */
	private:
		typename std::vector<std::forward_list<std::pair <Key, Val> > > _my_set;
		typename HeshFunction _Hesh;
	/* Constructors are here */
	public:
		HashTable(HeshFunction h = Hesh<Key>);
		explicit HashTable(size_t cap =  MaxSize, HeshFunction h = Hesh<Key>); 
		virtual ~HashTable() = default;

	/* Basic Commands*/
	public:
		bool insert(
};


#include "./hash_table.hpp"
#endif //  HASH_TABLE
