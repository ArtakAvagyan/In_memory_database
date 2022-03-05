/*
 * Redis -(Remote Dictionary Server) is an in-memory data structure, used as a distributed
 * in-memory database. Here you can see Lists, Sets, and Strings essential commands.
 *
 * */

#ifndef PARSER_H
#define PARSER_H

#include "./utility.h"
#include "../Vector/vector.h"
#include "../Forward_list/forward_list.h"
#include "../String/String.h"
#include "../Hash_table/hash_table.h"
#include "../List/List.h"
#include "../RBTree/rb_tree.h"


#include <iostream>
#include <algorithm>
#include <sstream> // escape if we can


class Redis
{
public:
	Redis();
	Redis(const Redis&) = delete;
	Redis(Redis&&) = delete;
	Redis& operator=(const Redis&) = delete;
	Redis& operator=(Redis&&) = delete;
public:
	String Parser(String&);

public:
	HashTable<String, RBTree<String>> _set;
	HashTable<String, List<String>> _list;
	HashTable<String, HashTable<String, String>> _map;
	HashTable<String, String> _string;
	HashTable<String, String(*) (Redis*, const Vector<String>&)> _function;

private:
	static String pushFrontList(Redis*, const Vector<String>&);
	static String pushBackList(Redis*, const Vector<String>&);
	static String getList(Redis*, const Vector<String>&);
	static String deleteList(Redis*, const Vector<String>&);
	static String insertSet(Redis*, const Vector<String>&);
	static String printSet(Redis*, const Vector<String>&);
	static String rPrintSet(Redis*, const Vector<String>&);
	static String ereseSet(Redis*, const Vector<String>&);
	static String insertMap(Redis*, const Vector<String>&);
	static String printMap(Redis*, const Vector<String>&);
	static String rPrintMap(Redis*, const Vector<String>&);
	static String delMap(Redis*, const Vector<String>&);
	static String addString(Redis*, const Vector<String>&);
	static String getString(Redis*, const Vector<String>&);
	static String concatString(Redis*, const Vector<String>&);


private:
	Vector<String> keywordParser(String&) const;
};
#include "parser.hpp"
#endif // PARSER_H
