template <typename T>
List<T>::List(const List<T>& other)
{
	for (auto it : other) 
	{	
		push_back(it);
	}
}
template <typename T>
List<T>::List(List<T>&& other)
{
	_head = other._head;
	_tail = other._tail;
	other._head = other._tail = nullptr;
}

template <typename T>
List<T>::List(const std::initializer_list<T>& other)
{
	for (const auto& it : other)
	{
		push_back(it);
	}
}
template <typename T>
List<T>::~List()
{
	try{
		clear();
	}
	catch(...)
	{
		std::cout << "che es shat lurj xndira LIST ic" <<std::endl;
		std::exit(0);
	}
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other)&
{
	List<T> tmp = other;
	std::swap(*this,tmp);
	return *this;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&&other)&
{
	clear();
	_head = other._head;
	_tail = other._tail;
	other._head = other._tail = nullptr;
	return *this;
}

template <typename T>
size_t List<T>::size()const
{
	int count{};
	for (auto it : *this){count++;}
	return count;
}

template <typename T>
bool List<T>::empty()const
{
	return _head == nullptr;
}
template <typename T>
void List<T>::clear()
{
	_tail = _head;
	while (_head)
	{
		_head = _head->_next;
		delete _tail;
		_tail = _head;
	}
	_head = _tail = nullptr;

}
template <typename T>
void List<T>::push_back(const T& elem)&
{
	if (!_head)
	{
		Node* tmp = new List<T>::Node (T());
		_head = new List<T>::Node(elem,tmp);
		tmp->_prev = _head ;
		_tail = _head;
	} else {
		_tail->_next = new List<T>::Node(elem,_tail->_next,_tail);
		_tail = _tail->_next;
		_tail->_next->_prev = _tail;
	}
}
template <typename T>
void List<T>::push_front(const T& elem)&
{
	if (!_head)
	{
		Node* tmp = new List<T>::Node(T());
		_head = new List<T>::Node(elem,tmp);
		tmp->_prev = _head ;
		_tail = _head;
	} else {
		_head->_prev = new List<T>::Node(elem,_head);
		_head = _head->_prev;
	}
}

template <typename T>
void List<T>::insert(List<T>::iterator it,const T& elem)&
{
	if (it._pointer->_prev == nullptr)
	{
		push_front(elem);
		return;
	}
	Node* prev = it._pointer->_prev;
	prev->_next = new List<T>::Node(elem,it._pointer,prev);
	it._pointer->_prev = prev->_next;
}

template <typename T>
void List<T>::erase(List<T>::iterator it)&
{
	if (it._pointer->_prev == nullptr)
	{
		_head= _head->_next;
		delete it._pointer;
		return;
	}
	Node* prev = it._pointer->_prev;
	prev->_next = it._pointer->_next;
	it._pointer->_prev = prev;
	delete it._pointer;

	
}
template <typename T>
List<T>::iterator::iterator(Node* ptr):_pointer{ptr} {}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()&
{
	_pointer = _pointer->_next;
	return *this;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++(int)&
{
	_pointer = _pointer->_next;
	return *this;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--()&
{
	_pointer = _pointer->_prev;
	return *this;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--(int)&
{
	_pointer = _pointer->_prev;
	return *this;
}

template <typename T>
T& List<T>::iterator::operator*()
{
	return _pointer->_elem;
}

template <typename T>
bool List<T>::iterator::operator==(const List<T>::iterator other)const
{
	return _pointer == other._pointer;
}

template <typename T>
bool List<T>::iterator::operator!=(const List<T>::iterator other)const
{
	return _pointer != other._pointer;
}
