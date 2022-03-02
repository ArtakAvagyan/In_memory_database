#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>

namespace UTIL
{

	namespace LIST
	{
		const std::string PUSH 		{ "LPUSH" };
		const std::string PUSH_BACK	{ "RPUSH" };
		const std::string PRINT_RENG	{ "LRANGE"};
		const std::string DELETE	{ "LTRIM" };
	}
	namespace SET
	{
		const std::string INSERT 	{ "SADD" };
		const std::string PRINT		{ "SMEMBERS" };
		const std::string RPRINT	{ "RSMEMBERS" };/*TAZA*/
		const std::string ERASE_F	{ "SPOP" };
		const std::string RAND_PRINT	{ "SRANDMEMBER" }; /*NOVU*/
	}
	namespace MAP
	{
		const std::string PRINT_REV	{ "ZREVRANGE" };
		const std::string DEL_ELEM	{ "ZREM" };
		const std::string PRINT_SIM	{ "ZINTER" };/*std::set_intersection*/ /*NOVU*/
		const std::string INSERT	{ "ZADD" };
		const std::string PRINT 	{ "ZRENGE" };
	}
	namespace STRING
	{
	
		const std::string CONCAT	{ "APPEND" };
		const std::string ADD_STR	{ "SET" };
		const std::string GET_VAL	{ "GET" };
	}
	const int COMAND{};
	const int NAME{1};
	const int PARAM{2};
}
#endif /* UTILITY_H */
