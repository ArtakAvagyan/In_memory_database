#include "Parser.h"
#include "Utility.h"

#include <boost/range/adaptor/reversed.hpp>

Redis::Redis():myFunction{
			{UTIL::LIST::PUSH, Redis::pushFrontList},
			{UTIL::LIST::PUSH_BACK, Redis::pushBackList},
			{UTIL::LIST::PRINT_RENG, Redis::getList},
			{UTIL::LIST::DELETE, Redis::deleteList},
			{UTIL::SET::INSERT, Redis::insertSet},
			{UTIL::SET::PRINT , Redis::printSet},
			{UTIL::SET::RPRINT , Redis::rPrintSet},
			{UTIL::SET::ERASE_F, Redis::ereseSet},
			{UTIL::MAP::PRINT_REV, Redis::rPrintMap},
			{UTIL::MAP::PRINT , Redis::printMap},
			{UTIL::MAP::INSERT , Redis::insertMap},
			{UTIL::MAP::DEL_ELEM, Redis::delMap},
			{UTIL::STRING::ADD_STR, Redis::addString},
			{UTIL::STRING::GET_VAL, Redis::getString},
			{UTIL::STRING::CONCAT, Redis::concatString}
			}{}

std::string Redis::Parser(std::string& fullLine)
{
	std::vector<std::string> tokens = keywordParser(fullLine);
	auto it = myFunction.find(tokens[UTIL::COMAND]);
	if (it != myFunction.end())
		return it->second(this , tokens);
	return {"Dont valid comand"};
}

std::vector<std::string> Redis::keywordParser(std::string& line)const
{
	std::stringstream stream(line);
	std::vector<std::string> tokens;
	while (!stream.eof())
	{
		std::string tmp;
		stream >> tmp;
		tokens.push_back(tmp);
	}
	return tokens;
}

std::string Redis::pushFrontList(Redis* redis, const std::vector<std::string>& tokens)
{
	if (3 > tokens.size()) { return "don't valid argument";}
	for ( size_t i = UTIL::PARAM ; i < tokens.size() ; ++i )
		redis->myList[tokens[UTIL::NAME]].push_front(tokens[i]);
	return {"ok"};
}

std::string Redis::pushBackList(Redis* redis, const std::vector<std::string>& tokens)
{
	if (3 > tokens.size()) { return "don't valid argument";}
	for ( size_t i = UTIL::PARAM ; i < tokens.size() ; ++i )
		redis->myList[ tokens[UTIL::NAME] ].push_back(tokens[i]);
	return {"ok"};
}

std::string Redis::getList(Redis* redis, const std::vector<std::string>& tokens)
{
	std::string str ;
	size_t count{1};
	for (auto& it : redis->myList[ tokens[UTIL::NAME] ])
	{
		if (it == "") {continue;}
		str += std::to_string(count++);
		str += " -> ";
		str += it ;
		str.push_back('\n');
	}
	return str;

}

std::string Redis::deleteList(Redis* redis, const std::vector<std::string>& tokens)
{
	redis->myList.erase(tokens[UTIL::NAME]);
	return {"ok"};
}

std::string Redis::insertSet(Redis* redis, const std::vector<std::string>& tokens)
{
	if (3 > tokens.size()) { return "don't valid argument";}
	for ( size_t i = UTIL::PARAM ; i < tokens.size() ; ++i ){std::cout<<tokens[i]<<std::endl;
		redis->mySet[ tokens[UTIL::NAME] ].insert(tokens[i]);}
	return {"ok"};
}

std::string Redis::printSet(Redis* redis, const std::vector<std::string>& tokens)
{
	std::string str ;
	size_t count{1};
	for (auto& it : redis->mySet[ tokens[UTIL::NAME] ])
	{
		std::cout<< it << std::endl;
		if (it == "") {continue;}
		str += std::to_string(count++);
		str += " -> ";
		str += it ;
		str.push_back('\n');
	}
	return str;
}

std::string Redis::rPrintSet(Redis* redis, const std::vector<std::string>& tokens)
{
	std::string str ;
	size_t count{1};
	for (auto& it : boost::adaptors::reverse(redis->mySet[ tokens[UTIL::NAME] ] ))
	{
		if (it == "") {continue;}
		str += std::to_string(count++);
		str += " -> ";
		str += it ;
		str.push_back('\n');
	}
	return str;
}
std::string Redis::ereseSet(Redis* redis, const std::vector<std::string>& tokens)
{
	redis->mySet[ tokens[UTIL::NAME] ].erase(redis->mySet[tokens[UTIL::NAME]].begin());
	return {"ok"};
}

std::string Redis::insertMap(Redis* redis, const std::vector<std::string>& tokens)
{
	if (3 > tokens.size()) { return "don't valid argument";}
	if (tokens.size() % 2 != 0) { return "don't valid argument";}
	for ( size_t i = UTIL::PARAM ; i < tokens.size() ; i+=2 )
		redis->myMap[ tokens[UTIL::NAME] ].insert(std::make_pair(tokens[i],tokens[i+1]));
	return {"ok"};
}

std::string Redis::printMap(Redis* redis, const std::vector<std::string>& tokens)
{
	std::string str ;
	size_t count{1};
	for (auto& it : redis->myMap[ tokens[UTIL::NAME] ])
	{
		if ( "" == it.first ||"" ==  it.second) {continue;}
		str += std::to_string(count++);
		str += " -> ";
		str += it.first + "  " + it.second;
		str.push_back('\n');
	}
	return str;
}

std::string Redis::rPrintMap(Redis* redis, const std::vector<std::string>& tokens)
{
	std::string str ;
	size_t count{1};
	for (auto& it : boost::adaptors::reverse(redis->myMap[ tokens[UTIL::NAME] ]))
	{
		if ( "" == it.first ||"" ==  it.second) {continue;}
		str += std::to_string(count++);
		str += " -> ";
		str += it.first + "  " + it.second;
		str.push_back('\n');
	}
	return str;
}

std::string Redis::delMap(Redis* redis, const std::vector<std::string>& tokens)
{
	if (3 > tokens.size()) { return "don't valid argument";}
	redis->myMap.erase( tokens[UTIL::NAME] );
	{
		return {"OK"};
	}
	return {"ENTER THE VALID PARAM !!"} ;
}

std::string Redis::addString(Redis* redis, const std::vector<std::string>& tokens)
{
	if (3 > tokens.size()) { return "don't valid argument";}
	redis->myString[tokens[UTIL::NAME]] = UTIL::PARAM;
	return {"ok"};
}

std::string Redis::getString(Redis* redis, const std::vector<std::string>& tokens)
{
	if (3 > tokens.size()) { return "don't valid argument";}
	auto it = redis->myString.find(tokens[UTIL::NAME]);
	if (it != redis->myString.end()) {return it->second ;}
	return {"dont have a this String"};
}

std::string Redis::concatString(Redis* redis, const std::vector<std::string>& tokens)
{
	if (3 > tokens.size()) { return "don't valid argument";}
	return redis->myString[tokens[UTIL::NAME]] += redis->myString[tokens[UTIL::PARAM]];
}

int main()
{
	Redis r;
	for (int i = 0 ; i  < 10 ; ++i)
	{
		std::string s;
		std::getline(std::cin, s);
		std::cout<< r.Parser(s) <<std::endl;
		
	}
	return 0;
}
