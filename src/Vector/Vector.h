#include <initializer_list>
#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector {
public:
	/* CONSTRUCTORS */
	Vector();   
	~Vector(); 
	Vector(int counter, const T& elem);           
	Vector(std::initializer_list<T> a);          
	Vector<T>(const Vector<T>& other);         
	/* OPERATORS */
	Vector<T>& operator=(const Vector<T>& other); 
	Vector<T>(Vector<T>&& rhs) noexcept;		  
	Vector<T>& operator=(Vector<T>&& rhs);        
	Vector<T> operator+(const Vector<T>& rhs);

public:
	/* MUTATOR FUNCTIONS */
	void push_back(const T& element);
	void push_front(const T& element);

	void erase(int size_pos);
	void resize(int s, const T& elem);

	/* ACCESSOR FUNCTIONS */
	T& operator[](const int iter) const;
	T& at(const int iter) const;

	int getCapacity() const;
	int getSize() const;

public:
	/* RA ITERATOR */
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


#include "vec_.hpp"
#endif // VECTOR_H
