#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <unordered_map>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <queue>
#include <iostream>
#include <set>
#include <sstream>

class Redis
{
public:
	Redis();
	Redis(const Redis&) = delete;
	Redis(Redis&&) = delete;
	Redis& operator=(const Redis&) = delete;
	Redis& operator=(Redis&&) = delete;
public:
	std::string Parser(std::string&);
private:
	static std::string pushFrontList(Redis*, const std::vector<std::string>&);
	static std::string pushBackList(Redis*, const std::vector<std::string>&);
	static std::string getList(Redis*, const std::vector<std::string>&);
	static std::string deleteList(Redis*, const std::vector<std::string>&);
	static std::string insertSet(Redis*, const std::vector<std::string>&);
	static std::string printSet(Redis*, const std::vector<std::string>&);
	static std::string rPrintSet(Redis*, const std::vector<std::string>&);
	static std::string ereseSet(Redis*, const std::vector<std::string>&);
	static std::string insertMap(Redis*, const std::vector<std::string>&);
	static std::string printMap(Redis*, const std::vector<std::string>&);
	static std::string rPrintMap(Redis*, const std::vector<std::string>&);
	static std::string delMap(Redis*, const std::vector<std::string>&);
	static std::string addString(Redis*, const std::vector<std::string>&);
	static std::string getString(Redis*, const std::vector<std::string>&);
	static std::string concatString(Redis*, const std::vector<std::string>&);
private:
	std::vector<std::string> keywordParser(std::string&)const;
private:
	std::map< std::string , std::set<std::string> > mySet;
	std::map< std::string , std::list<std::string> > myList;
	std::map<std::string , std::map<std::string,std::string> > myMap;
	std::map<std::string , std::string > myString;
	std::map<std::string , std::string(*)(Redis*,const std::vector<std::string>&) > myFunction;
};

#endif /* PARSER_H */
