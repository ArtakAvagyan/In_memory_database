#ifndef PQUEUE_H
#define PQUEUE_H

#include <cstddef>
#include <initializer_list>
#include <iterator>

template <typename T>
class PQueue
{
public:
	class iterator : public std::iterator<std::random_access_iterator_tag, T, ptrdiff_t , T* , T&>
	{
	public:
		iterator() = default;
		iterator(const iterator&) = default;
		iterator(iterator&&) = default;
		iterator& operator=(const iterator&) = default;
		iterator& operator=(iterator&&) = default;
		~iterator() = default;
		iterator(T*);
		iterator& operator++()&;
		iterator& operator++(int)&;
		iterator& operator--()&;
		iterator& operator--(int)&;
		iterator& operator+=(int)&;
		iterator operator+(int)const;
		iterator operator-(int)const;
		T& operator*();
		bool operator==(const iterator)const;
		bool operator!=(const iterator)const;

	private:
		T* _pointer;
	};
	iterator begin();
	iterator end();
public:
	PQueue();   
	~PQueue(); 
	PQueue(int counter, const T& elem);           
	PQueue(std::initializer_list<T> a);          
	PQueue(const PQueue& other);         
	
	PQueue<T>& operator=(const PQueue<T>& other); 
	PQueue<T>(PQueue<T>&& rhs) noexcept;		  
	PQueue<T>& operator=(PQueue<T>&& rhs);        
	PQueue<T> operator+(const PQueue<T>& rhs);
public:
	T& operator[](int pos);
	const T& operator[](const int pos) const;
	void insert(const T& elem);
	void erase(iterator);
private:
	void setPos();
private:
	size_t _size;
	size_t _cap;
	T* _buffer;
};

#include "PQueue.hpp"
#endif /* PQUEU_H */
