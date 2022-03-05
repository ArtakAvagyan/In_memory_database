#ifndef FORWARD_LIST
#define FORWARD_LIST

#include <initializer_list>
#include <iterator>
#include <iostream>

template <typename T>
class Forward_list
{
public:
	Forward_list();
	~Forward_list();
	explicit Forward_list(size_t count, const T& data);
	Forward_list(std::initializer_list<T> src);

	Forward_list(const Forward_list<T>&);
	Forward_list(Forward_list<T>&& src) noexcept;

	Forward_list<T>& operator=(const Forward_list<T>& rhs);
	Forward_list<T>& operator=(Forward_list<T>&& rhs) noexcept;

	bool operator==(const Forward_list<T>& rhs) const;
	bool operator!=(const Forward_list<T>& rhs) const;

	void push_front(const T& value);
	void push_back(const T& value);
	void removeAt(size_t index);
	void pop_front();
	void pop_back();

	void insertBefore(size_t pos, const T& value);
	void resize(size_t sz, const T& val = T());
		
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	size_t findIndex(const T& value) const;
	bool isEmpty() const;
	size_t getSize() const noexcept;
	void clear() noexcept;
	void reverse() noexcept; // recursive

private:
//	template <typename U>
	struct Node {
		T _data{};
		Node* _next{};
		Node() = default;
		Node(const T& elem , Node* next = nullptr)
			: _data{ elem }, _next{ next }{}
		Node(const Node& src)
			: _data{ src._data }, _next{ src._next }
		{}
		Node& operator=(const Node& src) {
			if (this == &src) return *this;
			_next = src._next;
			_data = src._data;
			return _data;
		}
	};
	size_t _size;
	Node* _head;

public:
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		constexpr iterator() = default;
		iterator(const iterator&) = default;
		iterator(iterator&&) = default;
		~iterator() = default;
		explicit iterator(Forward_list<T>::Node *b);
		
		iterator& operator=(const iterator& src) = default;
		iterator& operator=(iterator&&) = default;
		iterator& operator++() &;
		iterator& operator++(int) &;
		T& operator*();
		
		bool operator==(const iterator) const;
		bool operator!=(const iterator) const;

	private:
		Node *_buf;
	};
	iterator begin() {
		return iterator(_head);
	}
	iterator end() 
	{	
		return iterator(nullptr);	
	}

public:
	friend std::ostream& operator<<(std::ostream& os, const Forward_list<T>& src)
	{
		os << "Forward_list size is " << src._size << '\n';
		if (src._head == nullptr) return os;
		os << "Elements are : ";
		auto cur = src._head;
		while (cur->_next != nullptr) {
			os << cur->_data << " ";
			cur = cur->_next;
		}
		os << cur->_data << '\n';
		return os;
	}

private:
	Node* helperReverse(Node* head) noexcept;
	void helperDeleteNodes();
	void helperCopyingNodes(const Forward_list<T>& rhs);
};

#include "forward_list.hpp"
#endif // FORWARD_LIST
