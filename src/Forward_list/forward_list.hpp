#include "forward_list.h"

template <class T>
Forward_list<T>::Forward_list()
	: _size { 0 }, _head { nullptr }
{}

template <class T> 
Forward_list<T>::~Forward_list()
{
	helperDeleteNodes();
}

template <class T>
Forward_list<T>::Forward_list(size_t count, const T& data)
	: _size { count } , _head{ nullptr }
{
	if (_size == 0) return;
	this->_head = new Node;
	Node* cur = _head;
	cur->_data = data;
	while (--count)
	{
		cur->_next = new Node;
		cur = cur->_next;
		cur->_data = data;
	}
	cur->_next = nullptr;
}

template<class T>
Forward_list<T>::Forward_list(std::initializer_list<T> src)
	: _size { src.size() }, _head { nullptr }
{
	if (_size == 0) return;

	_head = new Node;
	Node* cur = _head;
	auto it = src.begin();
	while (it != src.end())
	{
		cur->_data = *it;
		it++;
		if (it != src.end()) {
			cur->_next = new Node;
			cur = cur->_next;
		}
	}
	cur->_next = nullptr;
}

template<class T>
Forward_list<T>::Forward_list(const Forward_list<T>& oth)
	: _size { oth._size }, _head { nullptr }
{
	if (_size == 0) return;
	helperCopyingNodes(oth);
}

template <class T>
Forward_list<T>::Forward_list(Forward_list<T>&& src) noexcept
	: _size{ src._size }, _head{ src._head }
{
	src._head = nullptr;
	src._size = 0;
}

template<class T>
Forward_list<T>& Forward_list<T>::operator=(const Forward_list<T>& rhs)
{
	if (this == &rhs) return *this;
	helperDeleteNodes();

	_size = rhs._size;
	if (_size == 0) return *this;
	
	helperCopyingNodes(rhs);
	return *this;
}

template<class T>
Forward_list<T>& Forward_list<T>::operator=(Forward_list<T>&& rhs) noexcept
{
	if (this == &rhs) return *this;

	helperDeleteNodes();
	_size = rhs._size;
	_head = rhs._head;

	rhs.head = nullptr;
	rhs.m_size = 0;
	return *this;
}

template <class T>
bool Forward_list<T>::operator==(const Forward_list<T>& rhs) const
{
	if (_size == rhs._size) {
		Node* cur = this->_head;
		Node* cur_2 = rhs._head;
		while (cur->_next != nullptr) {
			if (cur->_data != cur_2->_data) {
				return false;
			}
			cur = cur->_next;
			cur_2 = cur_2->_next;
		}
		return true;
	}
	return false;
}

template<class T>
bool Forward_list<T>::operator!=(const Forward_list<T>& rhs) const
{
	return !(*this == rhs);
}

template<class T>
inline size_t Forward_list<T>::getSize() const noexcept
{
	return this->_size;
}

template<class T>
void Forward_list<T>::clear() noexcept
{
	helperDeleteNodes();
}

template <class T>
void Forward_list<T>::push_back(const T& value)
{
	if (_head == nullptr) {
		push_front(value);
	}
	else {
		Node* prev = _head;
		
		while (prev->_next != nullptr) {
			prev = prev->_next;
		}
		prev->_next = new Node;
		
		prev->_next->_data = value;
		prev->_next->_next = nullptr;
		++_size;
	}
}

template<class T>
void Forward_list<T>::push_front(const T& value)
{
	Node* ptr = _head;
	_head = new Node;
	_head->_data = value;
	_head->_next = ptr;
	++_size;
}

template<class T>
void Forward_list<T>::pop_front()
{
	Node* first = _head;
	_head = _head->_next;
	delete first;
	--_size;
}

template <class T>
void Forward_list<T>::pop_back()
{
	if (_head == nullptr) {
		throw std::invalid_argument("pop_back() failed due to empty list");
	}
	--_size;
	Node* last = _head;
	while (last->_next->_next != nullptr) {
		last = last->_next;
	}
	Node* toDelete = last->_next;
	last->_next = nullptr;
	delete toDelete;
}

template <class T>
void Forward_list<T>::removeAt(size_t index)
{
	if (index >= _size) {
		std::cout << "Segmentation fault.\n";
		return;
	}
	else if (index == 0) pop_front();
	else {
		Node* prev = _head;
		for (int i = 0; i < index - 1; ++i) {
			prev = prev->_next;
		}
		Node* toDelete = prev->_next;
		prev->_next = toDelete->_next;

		delete toDelete;
		--_size;
	}
}

template<class T>
void Forward_list<T>::insertBefore(size_t pos, const T& value)
{
	if (pos < 0 || pos >= _size) {
		throw std::invalid_argument("Insertion failed due to invalid position.\n");
	}
	if (pos == 0) push_front(value);
	else {
		Node* prev = _head;
		for (int i = 0; i < pos - 1; ++i) {
			prev = prev->_next;
		}
		Node* cur = prev->_next;
		prev->_next = new Node;
		prev = prev->_next;

		prev->_data = value;
		prev->_next = cur;
		++_size;
	}
}


template<class T>
void Forward_list<T>::resize(size_t sz, const T& val) // works fine, debugger helped me.
{
	if (_size == sz) return;
	if (_size < sz) {
		Node* cur = _head;
		while (cur->_next != nullptr) {
			cur = cur->_next;
		}
		for (size_t i = _size; i < sz; ++i)
		{
			cur->_next = new Node;
			cur = cur->_next;
			cur->_data = val;
			++_size;
		}
		cur->_next = nullptr;
	}
	else {
		Node* cur = _head;
		while (--sz) {
			cur = cur->_next;
		}
		Node* forLastState = cur;
		cur = cur->_next;
		Node* toDelete = cur;
	
		while(cur != nullptr)
		{
			toDelete = cur;
			cur = cur->_next;
			delete toDelete;
			toDelete = nullptr;
			--_size;
		}
		forLastState->_next = nullptr;
	}
}

template<class T>
T& Forward_list<T>::front()
{
	return _head->_data;
}

template<class T>
const T& Forward_list<T>::front() const
{
	return _head->_data;
}

template <class T>
T& Forward_list<T>::back()
{
	Node* last = _head;
	while (last->_next != nullptr)
	{
		last = last->_next;
	}
	return last->_data;
}

template <class T>
const T& Forward_list<T>::back() const
{
	Node* last = _head;
	while (last->_next != nullptr)
	{
		last = last->_next;
	}
	return last->_data;
}

template<class T>
bool Forward_list<T>::isEmpty() const
{
	return _head == nullptr;
}

template<class T>
size_t Forward_list<T>::findIndex(const T& value) const
{
	Node* cur = _head;
	size_t count = 0;
	while (cur != nullptr)
	{
		if (cur->_data == value) return count;
		++count;
		cur = cur->_next;
	}
	return 0;
}

template <class T>
void Forward_list<T>::helperDeleteNodes()
{
	_size = 0;
	Node* tmp = _head;
	while (_head != nullptr)
	{
		_head = tmp->_next;
		delete tmp;
		tmp = _head;
	}
}

template<class T>
void Forward_list<T>::helperCopyingNodes(const Forward_list<T>& rhs)
{
	Node* cur_2 = rhs._head;
	this->_head = new Node;
	Node* cur = _head;
	cur->_data = cur_2->_data;

	while (cur_2->_next != nullptr) {
		cur_2 = cur_2->_next;
		cur->_next = new Node;
		cur = cur->_next;
		cur->_data = cur_2->_data;
	}
	cur->_next = nullptr;
}

template<class T>
void Forward_list<T>::reverse() noexcept
{
	_head = helperReverse(_head);
}

template<class T>
typename Forward_list<T>::Node* Forward_list<T>::helperReverse(Forward_list<T>::Node* head) noexcept
{
	if (head == nullptr || head->_next == nullptr) return head;
	Node* ptr = helperReverse(head->_next);
	head->_next->_next = head;
	head->_next = nullptr;
	return ptr;
}

template <typename T>
Forward_list<T>::iterator::iterator(Forward_list<T>::Node * b)
	: _buf { b }
{}		

template <typename T>
typename  Forward_list<T>::iterator& Forward_list<T>::iterator::operator++() & 
{
	_buf = _buf->_next;
	return *this;
}

template <typename T>
typename  Forward_list<T>::iterator& Forward_list<T>::iterator::operator++(int) &
{
	_buf = _buf->_next;
	return *this;
}

template <typename T>
T& Forward_list<T>::iterator::operator*()
{
	return _buf->_data;
}

template <typename T>
bool Forward_list<T>::iterator::operator==(const Forward_list<T>::iterator it) const
{
	return this->_buf == it._buf;
}

template <typename T>
bool Forward_list<T>::iterator::operator!=(const  Forward_list<T>::iterator it) const
{
	return this->_buf != it._buf;
}
