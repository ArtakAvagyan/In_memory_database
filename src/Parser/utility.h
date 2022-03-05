#ifndef UTILITY_H
#define UTILITY_H

#include "../String/String.h"

namespace UTIL
{

	namespace LIST
	{
		const String PUSH 	{ "LPUSH" };
		const String PUSH_BACK	{ "RPUSH" };
		const String PRINT_RENG	{ "LRANGE"};
		const String DELETE	{ "LTRIM" };
	}
	namespace SET
	{
		const String INSERT 	{ "SADD" };
		const String PRINT	{ "SMEMBERS" };
		const String RPRINT	{ "RSMEMBERS" };
		const String ERASE_F	{ "SPOP" };
	}
	namespace PQ
	{
		const String PRINT_REV	{ "ZREVRANGE" };
		const String DEL_ELEM	{ "ZREM" };
		const String INSERT	{ "ZADD" };
		const String PRINT 	{ "ZRENGE" };
	}
	namespace STRING
	{
	
		const String CONCAT	{ "APPEND" };
		const String ADD_STR	{ "SET" };
		const String GET_VAL	{ "GET" };
	}
	const int COMMAND {};
	const int NAME {1};
	const int PARAM {2};
	
	String to_String(size_t s)
	{
		String str;
		while (s)
		{
			str.push_back(('0'+s%10));
			s/=10;
		}
		return str;
	}
}
#endif /* UTILITY_H */
