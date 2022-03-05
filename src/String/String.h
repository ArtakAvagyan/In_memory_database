#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>
#include <sstream>

class String
{
public:
      String();
      explicit String(size_t , char ch = '\0');
      String(const char*);
      String(const String&);
      String(String&&)noexcept;
      ~String();
public:
      const size_t size()const;
      char& at(size_t);
      const char& at(size_t)const;
      void push_back(const char ch);
      void clear();
public:
      char& operator[](size_t);
      const char& operator[](size_t)const;
      String& operator=(const String&)&;
      String& operator=(const char*)&;
      String& operator=(String&&)&;
      bool operator==(const String&)const;
      bool operator!=(const String&)const;
      bool operator>(const String&)const;
      bool operator<(const String&)const;
      bool operator>=(const String&)const;
      bool operator<=(const String&)const;
      String operator+(const String&)const;
      String& operator+=(const String&)&;
      friend std::istream& operator>>(std::istream&, String&);
public:
	class iterator : public std::iterator<std::random_access_iterator_tag,char>
	{
	public:
		iterator() = default;
		iterator(const iterator&) = default;
		iterator(iterator&&) = default;
		iterator& operator=(const iterator&) = default;
		iterator& operator=(iterator &&) = default;
		~iterator() = default;
		iterator(char*);
		iterator& operator++()&;
		iterator& operator++(int)&;
		iterator& operator--()&;
		iterator& operator--(int)&;
		iterator& operator+=(int)&;
		iterator operator+(int)const;
		char& operator*();
		bool operator==(const iterator)const;
		bool operator!=(const iterator)const;
	private:
		char* _pointer;
	};
public:
	iterator begin()
	{
		return _buffer; 
	}
	iterator end()
	{
		return _buffer + _size;
	}
private:
	size_t _size{};
	size_t _capacity{};
	char* _buffer;
};

std::ostream& operator<<(std::ostream& os , const String& str)
{
	os << &str[0];
	return os;
}
std::istream& operator>>(std::istream& is,String& str)
{
	static char ch [255]; 
	is >> ch;
	str = ch;
	return is;

}

#include "String.hpp"
#endif /* STRING_H */
