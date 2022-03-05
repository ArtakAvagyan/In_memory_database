#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <initializer_list>

template <typename T>
class List
{
private:
	struct Node
	{
		T _elem;
		Node* _next;
		Node* _prev;
		Node(const T& elem, Node* next = nullptr, Node* prev = nullptr)
			:_elem{ elem }, _next{ next }, _prev{ prev }{}
	};
public:
	class iterator : public std::iterator<std::bidirectional_iterator_tag,T>
	{
	public:
                iterator() = default;
                iterator(const iterator&) = default;
                iterator(iterator&&) = default;
                iterator& operator=(const iterator&) = default;
                iterator& operator=(iterator &&) = default;
                ~iterator() = default;
                iterator(Node*);
                iterator& operator++()&;
                iterator& operator++(int)&;
                iterator& operator--()&;
                iterator& operator--(int)&;
                T& operator*();
                bool operator==(const iterator)const;
                bool operator!=(const iterator)const;	
	private:
	friend class List;
	Node* _pointer;
	};
public:
	List() = default;
	List(const List&);
	List(List&&);
	List(const std::initializer_list<T>&);
	~List();
public:
	List& operator=(const List&)&;
	List& operator=(List&&)&;
	size_t size()const;
	bool empty()const;
	void clear();
	void push_back(const T&)&;
	void push_front(const T&)&;
	void insert(iterator,const T&)&;
	List<T>::iterator begin()
	{
		List<T>::iterator it = _head;
		return it;
	}
	List<T>::iterator end()
	{
		List<T>::iterator it = _tail->_next;
		return it;
	}
	void erase(iterator)&;
private:
	List<T>::iterator begin()const
	{
		List<T>::iterator it = _head;
		return it;
	}
	List<T>::iterator end()const
	{
		if (_head == nullptr)
		{
			return nullptr;
		}
		List<T>::iterator it = _tail->_next;
		return it;
	}

private:
	Node* _head{};
	Node* _tail{};
};

#include "List.hpp"
#endif /* LIST_H */
