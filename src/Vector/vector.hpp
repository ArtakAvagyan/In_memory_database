#include "vector.h"

template<typename T>
Vector<T>::Vector() : m_size{}, m_cap{}, m_arr{ nullptr }
{}

template<typename T>
Vector<T>::~Vector() {
	if (m_arr!= nullptr) { delete[] m_arr; }
}

template<typename T>
Vector<T>::Vector(int counter, const T& elem) : m_size{}, m_cap{} {
	if (counter > 0) {
		m_size = counter;
		m_cap = counter;
		m_arr = new T[m_cap];
		for (int i = 0; i < m_size; ++i) {
			m_arr[i] = elem;
		}
	}
	else {
		std::cout << "Counter must be positive number.\n";
		exit(-1);
	}
}
template<typename T>
Vector<T>::Vector(Vector&& rhs) noexcept{
	this->m_size = rhs.m_size;
	this->m_cap = rhs.m_cap;
	this->m_arr = rhs.m_arr;
	rhs.m_arr = nullptr;
	rhs.m_size = 0;
	rhs.m_cap = 0;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) {
	m_cap = other.m_cap;
	m_size = other.m_size;
	m_arr = new T[m_cap];
	for (int i = 0; i < m_size; ++i) {
		m_arr[i] = other.m_arr[i];
	}
}
template<typename T>
Vector<T>::Vector(std::initializer_list<T> a) : m_size{ (int)a.size() }, m_cap{ (int)a.size() }{
	int i = {};
	m_arr = new T[m_cap];
	for (const auto& a1 : a) {
		m_arr[i++] = a1;
	}
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (this == &other) {
		return *this;
	}
	if (m_cap >= other.m_size) {
		m_size = other.m_size;
		for (int i = 0; i < m_size; ++i) {
			m_arr[i] = other.m_arr[i];
		}
	}
	else {
		delete[] m_arr;
		m_cap = other.m_cap;
		m_size = other.m_size;
		m_arr = new T[m_cap];
		for (int i = 0; i < m_size; ++i) {
			m_arr[i] = other.m_arr[i];
		}
	}
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
	if (this == &other) {
		return *this;
	}
	this->m_size = other.m_size;
	this->m_cap = other.m_cap;
	this->m_arr = other.m_arr;
	other.m_arr = nullptr;
	other.m_size = 0;
	other.m_cap = 0;
	return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector& oth) {
	Vector<T> r;
	r.m_cap = this->m_cap + oth.m_cap;
	r.m_size = this->m_size + oth.m_size;
	r.m_arr = new T[r.m_cap];
	for (int i = 0; i < this->m_size; ++i)
		r.m_arr[i] = this->m_arr[i];
	int i = 0;
	for (int j = this->m_size; j < r.m_size; ++j) {
		i++;
		r.m_arr[j] = oth.m_arr[i];
	}
	return r;
}

template <typename T>
const T& Vector<T>::at(const int pos) const {
	if (pos >= 0 && pos < m_size) {
		return m_arr[pos];
	}
	else {
		throw std::out_of_range("Segmentation fault - run time error\n");
	}
}

template <typename T>
T& Vector<T>::at(int pos)
{
	if(pos >= 0 && pos < m_size) {
		return m_arr[pos];
	} else {
		throw std::out_of_range("Segmentation fault - run time error\n");
	}
}

template<typename T>
const T& Vector<T>::operator[](const int pos) const {
		return m_arr[pos];
}

template <typename T>
T& Vector<T>::operator[](int pos)
{
	return m_arr[pos];
}

template<typename T>
void Vector<T>::push_back(const T& element) {
	if (m_cap == m_size) {
		m_cap = m_cap ? m_cap * 2 : 1;
		T* tmp = new T[m_cap];
		for (int i = 0; i < m_size; ++i) {
			tmp[i] = this->m_arr[i];
		}
		delete[] m_arr;
		m_arr = tmp;
	}
	m_arr[m_size] = element;
	++m_size;
}


template<typename T>
void Vector<T>::push_front(const T& element) {
	if (m_size == m_cap) {
		m_cap = m_cap ? m_cap * 2 : 1;
		T* tmp = new T[m_cap];
		
		for (int i = 0; i < m_size; ++i) {
			tmp[i + 1] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = tmp;
	}
	else {
		for (int i = m_size - 1; i >= 0; --i) {
			m_arr[i + 1] = m_arr[i];
		}
	}
	m_arr[0] = element;
	++m_size;
}

template<typename T>
inline void Vector<T>::erase(int size_pos) {
	if (size_pos >= 0 && size_pos < m_size)
	{
		for (int i = size_pos; i < m_size - 1; ++i){
			m_arr[i] = m_arr[i + 1];
		}
		--m_size;
	}
}

template <typename T>
void Vector<T>::resize(const size_t s,const T& elem) {
	if (s < m_size) {
		m_size = s;
	} else {
		if (s <= m_cap) {
			for (int i = m_size; i < s; ++i) {
				m_arr[i] = elem;
			}
			m_size = s;
		} else {
			T* tmp = new T[s];
			for (int i = 0; i < m_size; ++i) {
				tmp[i] = m_arr[i];
			}
			for (int i = m_size; i < s; ++i) {
				tmp[i] = elem;
			}
			delete[] m_arr;
			m_arr = tmp;
			m_size = m_cap = s;
		}
	}
}

template <typename T>
size_t Vector<T>::getCapacity() const {
	return m_cap;
}

template <typename T>
size_t Vector<T>::getSize() const {
	return m_size;
}
/* Iterators */
template <typename T>
Vector<T>::iterator::iterator(T* ptr) :_pointer{ ptr } {}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator++()&
{
	_pointer += 1;
	return *this;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator++(int)&
{
	_pointer += 1;
	return *this;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator--()&
{
	_pointer -= 1;
	return *this;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator--(int)&
{
	_pointer -= 1;
	return *this;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator+=(int pos)&
{
	_pointer += pos;
	return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator+(int pos)const
{
	typename Vector<T>::iterator tmp = *this;
	tmp += pos;
	return tmp;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator-(int count) const
{
	return this->_pointer - count;
}

template <typename T>
T& Vector<T>::iterator::operator*()
{
	return *_pointer;
}

template <typename T>
bool Vector<T>::iterator::operator==(const Vector<T>::iterator other)const
{
	return _pointer == other._pointer;
}

template <typename T>
bool Vector<T>::iterator::operator!=(const Vector<T>::iterator other)const
{
	return _pointer != other._pointer;
}
