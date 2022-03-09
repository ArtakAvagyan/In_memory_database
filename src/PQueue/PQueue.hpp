#include "PQueue.h"
template<typename T>
PQueue<T>::PQueue() : _size{}, _cap{2}, _buffer{}
{
	_buffer = new T[_cap];
}

template<typename T>
PQueue<T>::~PQueue() 
{
	if (_buffer!= nullptr) { delete[] _buffer; }
}

template<typename T>
PQueue<T>::PQueue(PQueue&& rhs) noexcept
{
	this->_size = rhs._size;
	this->_cap = rhs._cap;
	this->_buffer = rhs._buffer;
	rhs._buffer = nullptr;
	rhs._size = 0;
	rhs._cap = 0;
}

template<typename T>
PQueue<T>::PQueue(const PQueue<T>& other) 
{
	_cap = other._cap;
	_size = other._size;
	_buffer = new T[_cap];
	for (int i = 0; i < _size; ++i) {
		_buffer[i] = other._buffer[i];
	}
}

template<typename T>
PQueue<T>::PQueue(std::initializer_list<T> a)
	: _size{ (int)a.size() }, _cap{ (int)a.size() }
{
	int i = {};
	_buffer = new T[_cap];
	for (const auto& a1 : a) 
	{
		insert(a1);
	}
}

template<typename T>
PQueue<T>& PQueue<T>::operator=(const PQueue& other) 
{
	if (this == &other) {
		return *this;
	}
	if (_cap >= other._size) {
		_size = other._size;
		for (int i = 0; i < _size; ++i) {
			_buffer[i] = other._buffer[i];
		}
	}
	else {
		delete[] _buffer;
		_cap = other._cap;
		_size = other._size;
		_buffer = new T[_cap];
		for (int i = 0; i < _size; ++i) {
			_buffer[i] = other._buffer[i];
		}
	}
	return *this;
}

template<typename T>
PQueue<T>& PQueue<T>::operator=(PQueue&& other) 
{
	if (this == &other) {
		return *this;
	}
	this->_size = other._size;
	this->_cap = other._cap;
	this->_buffer = other._buffer;
	other._buffer = nullptr;
	other._size = 0;
	other._cap = 0;
	return *this;
}

template<typename T>
PQueue<T> PQueue<T>::operator+(const PQueue& oth) 
{
	PQueue<T> r;
	r._cap = this->_cap + oth._cap;
	r._size = this->_size + oth._size;
	r._buffer = new T[r._cap];
	for (int i = 0; i < this->_size; ++i)
		r._buffer[i] = this->_buffer[i];
	int i = 0;
	for (int j = this->_size; j < r._size; ++j) {
		i++;
		r._buffer[j] = oth._buffer[i];
	}
	return r;
}


template<typename T>
void PQueue<T>::insert(const T& elem)
{
	if (_size >= _cap)
	{
		_cap *= 2;
		T* tmp = new T[_cap];
		for (size_t i = 0 ; i < _size ; ++i )
			tmp[i] = _buffer[i];
		delete[] _buffer;
		_buffer = tmp;
		tmp = nullptr;
	}
	_buffer[_size++] = elem;
	setPos();
}

template<typename T>
void PQueue<T>::erase(PQueue<T>::iterator it)
{
	auto next = std::next(it);
	while (next != end())
	{
		*it = *next;
		next++;
		it++;
	}
	_size--;
}

template<typename T>
void PQueue<T>::setPos()
{
	T target = _buffer[_size-1];
	size_t i = _size-2;
	while ( i < _size && _buffer[i] < target)
	{
		_buffer[i+1] = _buffer[i];
		--i;
	}
	_buffer[i+1] = target;
}

template <typename T>
typename PQueue<T>::iterator PQueue<T>::begin()
{
	return _buffer;
}

template <typename T>
typename PQueue<T>::iterator PQueue<T>::end()
{
	return (_buffer + _size);
}
template <typename T>
PQueue<T>::iterator::iterator(T* ptr) :_pointer{ ptr } {}

template <typename T>
typename PQueue<T>::iterator& PQueue<T>::iterator::operator++()&
{
	_pointer += 1;
	return *this;
}

template <typename T>
typename PQueue<T>::iterator& PQueue<T>::iterator::operator++(int)&
{
	_pointer += 1;
	return *this;
}

template <typename T>
typename PQueue<T>::iterator& PQueue<T>::iterator::operator--()&
{
	_pointer -= 1;
	return *this;
}

template <typename T>
typename PQueue<T>::iterator& PQueue<T>::iterator::operator--(int)&
{
	_pointer -= 1;
	return *this;
}

template <typename T>
typename PQueue<T>::iterator& PQueue<T>::iterator::operator+=(int pos)&
{
	_pointer += pos;
	return *this;
}

template <typename T>
typename PQueue<T>::iterator PQueue<T>::iterator::operator+(int pos)const
{
	typename PQueue<T>::iterator tmp = *this;
	tmp += pos;
	return tmp;
}

template <typename T>
typename PQueue<T>::iterator PQueue<T>::iterator::operator-(int count) const
{
	return this->_pointer - count;
}

template <typename T>
T& PQueue<T>::iterator::operator*()
{
	return *_pointer;
}

template <typename T>
bool PQueue<T>::iterator::operator==(const PQueue<T>::iterator other)const
{
	return _pointer == other._pointer;
}

template <typename T>
bool PQueue<T>::iterator::operator!=(const PQueue<T>::iterator other)const
{
	return _pointer != other._pointer;
}
