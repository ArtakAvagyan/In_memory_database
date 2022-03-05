String::String():_size{0},_capacity{16}
{
	_buffer = new char[_capacity];
	_buffer[_size] = '\0';
}

void String::clear()
{
	_size = 0 ;
	_buffer[_size] = '\0';
}

String::String(size_t  size, char  ch):_size{size},_capacity{size + 1}
{
	_buffer = new char[_capacity];
	for (int i = 0 ; i < _size ; ++i)
	{
		_buffer[i] = ch;
	}
	_buffer[_size]= '\0';
}


String::String(const char* str)
{
	_size = std::strlen(str);
	_capacity = _size +1;
	_buffer = new char[_capacity];
	for (int i = 0 ; i <= _size ; ++i)
	{
		_buffer[i] = str[i];
	}
	_buffer[_size]= '\0';
}

String::String(const String& str):_size{str._size},_capacity{str._capacity}
{
	_buffer = new char[_capacity];
	for (int i = 0 ; i <= _size ; ++i)
	{
		_buffer[i] = str._buffer[i];
	}
}


String::String(String&& str) noexcept
		:_size{std::move(str._size)},_capacity{std::move(str._capacity)},_buffer{std::move(str._buffer)}{}

String::~String()
{
	if(_buffer)
		delete[]_buffer;
}

inline const size_t String::size()const
{
	return _size;
}
inline char& String::at(size_t pos)
{
	if(_size <= pos)
		throw std::out_of_range("es ur ??");
	return _buffer[pos];
}
inline const char& String::at(size_t pos)const
{
	if(_size <= pos)
		throw std::out_of_range("es ur ??");
	return _buffer[pos];
}

String& String::operator=(const String& str)&
{
	if(this == &str) {return *this;}
      	delete[] _buffer;
      	_size = str._size;
      	_buffer = new char[ _size+1];
      	for (int i = 0 ; i < _size ; ++i)
      	{
        	    _buffer[i] = str._buffer[i];
      	}
      	_buffer[_size] = '\0';
      	return *this ;

}

String& String::operator=(const char* ch)&
{
      delete[] _buffer;
      _size = std::strlen(ch);
      _buffer = new char[ _size+1];
      for (int i = 0 ; i < _size ; ++i)
      {
            _buffer[i] = ch[i];
      }
      _buffer[_size] = '\0';
      return *this ;
}


String& String::operator=(String&& str)&
{
	delete[]_buffer;
	_size = str._size;
	_capacity = str._capacity;
	_buffer = str._buffer;
	str._buffer = nullptr;
	return *this;
}

char& String::operator[](size_t pos)
{
	return _buffer[pos];
}

const char& String::operator[](size_t pos)const
{
	return _buffer[pos];
}

bool String::operator==(const String& s)const
{
	if (s.size() != _size) {return false;}
	for (int i = 0 ; i < _size ; ++i)
	{
		if(s._buffer[i] != _buffer[i])
		{
			return false;
		}
	}
	return true;
}

bool String::operator!=(const String& s)const
{
	if (s.size() != _size) {return true;}
	for (int i = 0 ; i < _size ; ++i)
	{
		if(s._buffer[i] != _buffer[i])
		{
			return true;
		}
	}
	return false;
}

bool String::operator>(const String& str)const
{
	size_t size = str._size > _size ? _size : str._size ;
	for (int i = 0 ; i < size ; ++i)
	{
		if(_buffer[i] > str._buffer[i])
		{
			return true;
		}
	}
	return false;
}

bool String::operator<(const String& str)const
{
	size_t size = str._size > _size ? _size : str._size ;
	for (int i = 0 ; i < size ; ++i)
	{
		if(_buffer[i] < str._buffer[i])
		{
			return true;
		}
	}
	return false;
}
 
bool String::operator>=(const String& str)const
{
	size_t size = str._size > _size ? _size : str._size ;
	for (int i = 0 ; i < size ; ++i)
	{
		if(_buffer[i] < str._buffer[i])
		{
			return false;
		}
	}
	return true;
}

bool String::operator<=(const String& str)const
{
	size_t size = str._size > _size ? _size : str._size ;
	for (int i = 0 ; i < size ; ++i)
	{
		if(_buffer[i] > str._buffer[i])
		{
			return true;
		}
	}
	return false;
}

String String::operator+(const String& other)const
{
	String tmp = *this;
	tmp += other;
	return tmp;
}


String& String::operator+=(const String& other)&
{
	for (size_t i = 0 ; i < other._size ; ++i)
	{
		push_back(other[i]);
	}
	return *this;
}

void String::push_back(const char ch)
{
	if (_size + 1 >= _capacity)
	{
		_capacity *= 2;
		char* tmp = new char[_capacity];
		for (int i = 0 ; i < _size; ++i)
		{
			tmp[i] = _buffer[i];
		}
		delete[]_buffer;
		_buffer = tmp;
		tmp = nullptr;
	}
	_buffer[_size] = ch;
	_buffer[++_size] = '\0';
}

String::iterator::iterator(char* ptr)
	:_pointer{ptr} {}

String::iterator& String::iterator::operator++()&
{
	_pointer+=1;
	return *this;
}

String::iterator& String::iterator::operator++(int)&
{
	_pointer+=1;
	return *this;
}

String::iterator& String::iterator::operator--()&
{
	_pointer-=1;
	return *this;
}

String::iterator& String::iterator::operator--(int)&
{
	_pointer-=1;
	return *this;
}

String::iterator& String::iterator::operator+=(int pos)&
{
	_pointer+= pos;
	return *this;
}

String::iterator String::iterator::operator+(int pos)const
{
	String::iterator tmp = *this ;
	tmp+= pos;
	return tmp;
}

char& String::iterator::operator*()
{
	return *_pointer;
}

bool String::iterator::operator==(const String::iterator other)const
{
	return _pointer == other._pointer;
}
bool String::iterator::operator!=(const String::iterator other)const
{
	return _pointer != other._pointer;
}
