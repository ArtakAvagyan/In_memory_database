#ifndef VECTOR_H
#define VECTOR_H

#include<initializer_list>
#include<cstddef>

template <class T>
class Vector {
public:
	Vector();   
	~Vector(); 
	Vector(int counter, const T& elem);           
	Vector(std::initializer_list<T> a);          
	Vector<T>(const Vector<T>& other);         
	
	Vector<T>& operator=(const Vector<T>& other); 
	Vector<T>(Vector<T>&& rhs) noexcept;		  
	Vector<T>& operator=(Vector<T>&& rhs);        
	Vector<T> operator+(const Vector<T>& rhs);

public:
	void push_back(const T& element);
	void push_front(const T& element);

	void erase(int size_pos);
	void resize(const size_t s,const T& elem);

	const T& operator[](const int pos) const;
	const T& at(const int pos) const;

	T& operator[](int pos);
	T& at(int pos);

	size_t getCapacity() const;
	size_t getSize() const;

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
		iterator operator-(int) const;
		T& operator*();
		bool operator==(const iterator)const;
		bool operator!=(const iterator)const;

private:
	T* _pointer;
};
	  iterator begin() 
	  {
		  iterator a = m_arr;
		  return a;
	  }

	  iterator end()
	  {
		  iterator a = m_arr + m_size;
		  return a;
	  }
private:
	int m_size;
	int m_cap;
	T* m_arr;
};


#include "vector.hpp"
#endif // VECTOR_H
