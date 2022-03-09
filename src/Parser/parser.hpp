#include "parser.h"

Redis::Redis(){

		_function.insert(UTIL::LIST::PUSH, Redis::pushFrontList);
		_function.insert(UTIL::LIST::PUSH_BACK, Redis::pushBackList);
		_function.insert(UTIL::LIST::PRINT_RENG, Redis::getList);
		_function.insert(UTIL::LIST::DELETE, Redis::deleteList);
		_function.insert(UTIL::SET::INSERT, Redis::insertSet);
		_function.insert(UTIL::SET::PRINT , Redis::printSet);
		_function.insert(UTIL::SET::RPRINT , Redis::rPrintSet);
		_function.insert(UTIL::SET::ERASE_F, Redis::ereseSet);
		_function.insert(UTIL::PQ::PRINT_REV, Redis::rPrintPQ);
		_function.insert(UTIL::PQ::PRINT , Redis::printPQ);
		_function.insert(UTIL::PQ::INSERT , Redis::insertPQ);
		_function.insert(UTIL::PQ::DEL_ELEM, Redis::delPQ);
		_function.insert(UTIL::STRING::ADD_STR, Redis::addString);
		_function.insert(UTIL::STRING::GET_VAL, Redis::getString);
		_function.insert(UTIL::STRING::CONCAT, Redis::concatString);
		}

String Redis::Parser(String& str)
{
	Vector<String> tokens = keywordParser(str);
	try{
		return (_function.find(tokens[UTIL::COMMAND])(this,tokens));
	}
	catch(const std::out_of_range& )
	{
		return String("Enter valid command, please.");
	}
	return String("Ok");
}

Vector<String> Redis::keywordParser(String& line) const
{
	String str;
	Vector<String> tokens;
	for (auto ch : line)
	{
		if (ch == ' ' || ch == '\0')
		{
			tokens.push_back(str);
			str = "";
		} else {
			str.push_back(ch);
		}
	}
	tokens.push_back(str);
	return tokens;
}


String Redis::pushFrontList(Redis* _redis, const Vector<String>& tokens)
{
	if (tokens.getSize() < 3) { return "Argument is not valid.";}
	for ( size_t i = UTIL::PARAM ; i < tokens.getSize() ; ++i )
		_redis->_list[tokens[UTIL::NAME]].push_front(tokens[i]);
	return String("Ok");
}

String Redis::pushBackList(Redis* redis, const Vector<String>& tokens)
{
	if (3 > tokens.getSize()) { return "Argument is not valid.";}
	for ( size_t i = UTIL::PARAM ; i < tokens.getSize() ; ++i )
		redis->_list[ tokens[UTIL::NAME] ].push_back(tokens[i]);
	return {"Ok"};
}

String Redis::getList(Redis* redis, const Vector<String>& tokens)
{
	String str ;
	size_t count{1};
	for (auto& it : redis->_list[ tokens[UTIL::NAME] ])
	{
		if (it == "") {continue;}
		str += UTIL::to_String(count++);
		str += " -> ";
		str += it ;
		str.push_back('\n');
	}
	std::cout<< str <<std::endl;
	return str;

}

String Redis::deleteList(Redis* redis, const Vector<String>& tokens)
{
	redis->_list.erase(tokens[UTIL::NAME]);
	return {"Ok"};
}

String Redis::insertSet(Redis* redis, const Vector<String>& tokens)
{
	if (3 > tokens.getSize()) { return "don't valid argument";}
	for ( size_t i = UTIL::PARAM ; i < tokens.getSize() ; ++i )
	{
		redis->_set[tokens[UTIL::NAME]].insert(tokens[i]);
	}
	return {"Ok"};
}
String Redis::printSet(Redis* redis, const Vector<String>& tokens)
{
	 String str ;
	 size_t count{1};
	 Vector<String> resalt =  redis->_set[tokens[UTIL::NAME]].print();
	 for (auto it : resalt)
	 {
		if (it == "") {continue;}
		str += UTIL::to_String(count++);
		str += " -> ";
		str += it ;
		str.push_back('\n');
	 }
	 return str;
}

String Redis::rPrintSet(Redis* redis, const Vector<String>& tokens)
{
	 String str ;
	 size_t count{1};
	 Vector<String> resalt =  redis->_set[tokens[UTIL::NAME]].print();
	 for (auto it = resalt.end() ; it != resalt.begin() ;)
	 {
		--it;
		if (*it == "") {continue;}
		str += UTIL::to_String(count++);
		str += " -> ";
		str += *it ;
		str.push_back('\n');
	 }
	 return str;

}


String Redis::ereseSet(Redis* redis, const Vector<String>& tokens)
{
	redis->_set[ tokens[UTIL::NAME] ].clear();
	return {"Ok"};
}

String Redis::addString(Redis* redis, const Vector<String>& tokens)
{
	if (3 > tokens.getSize()) { return "Argument is not valid.";}
	redis->_string[tokens[UTIL::NAME]] = tokens[UTIL::PARAM];
	return {"ok"};
}

String Redis::getString(Redis* redis, const Vector<String>& tokens)
{
	try{
		return redis->_string.find(tokens[UTIL::NAME]);
	}
	catch(const std::out_of_range&)
	{
		return String("dont have a this String");
	}
	return String ("OK");
}

String Redis::concatString(Redis* redis, const Vector<String>& tokens)
{
	if (3 > tokens.getSize()) { return "Argument is not valid.";}
	return redis->_string[tokens[UTIL::NAME]] += redis->_string[tokens[UTIL::PARAM]];
}

String Redis::printPQ(Redis* redis, const Vector<String>& tokens)
{
	 String str ;
	 size_t count{1};
	 for (auto it : redis->_pq[tokens[UTIL::NAME]])
	 {
		str += UTIL::to_String(count++);
		str += " -> ";
		str += it.first;
		str += "   ";
		str += it.second; 
		str.push_back('\n');
	 }
	 return str;
}

String Redis::rPrintPQ(Redis* redis, const Vector<String>& tokens)
{
	 String str ;
	 size_t count{1};
	 for (auto it = redis->_pq[tokens[UTIL::NAME]].end() ; it != redis->_pq[tokens[UTIL::NAME]].begin() ;)
	 {
		--it;
		auto i = *it;
		str += UTIL::to_String(count++);
		str += " -> ";
		str += i.first;
		str += "   ";
		str += i.second;
		str.push_back('\n');
	 }
	 return str;

}


String Redis::insertPQ(Redis* redis, const Vector<String>& tokens)
{
	if (4 > tokens.getSize()) { return "Argument is not valid";}
	for ( size_t i = UTIL::PARAM ; i < tokens.getSize() ; i+=2 )
	{
		redis->_pq[tokens[UTIL::NAME]].insert(pair<String,String>(tokens[i],tokens[i+1]));
	}
	return {"Ok"};
}

String Redis::delPQ(Redis* redis, const Vector<String>& tokens)
{
		redis->_pq[tokens[UTIL::NAME]].erase(redis->_pq[tokens[UTIL::NAME]].begin());
	return {"Ok"};
}
