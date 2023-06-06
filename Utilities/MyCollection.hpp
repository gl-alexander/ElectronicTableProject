#pragma once
#include <iostream>

const size_t DEFAULT_CAPACITY = 8;

template <class T>
class MyCollection
{

	T** _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;

	void free();
	void copyFrom(const MyCollection<T>& other);
	void moveFrom(MyCollection<T>&& other);
	void resize(size_t newCapacity);



public:
	MyCollection() = default;
	MyCollection(const MyCollection<T>& other);
	MyCollection(MyCollection<T>&& other) noexcept;
	MyCollection& operator=(const MyCollection<T>& other);
	MyCollection& operator=(MyCollection<T>&& other) noexcept;
	~MyCollection();

	MyCollection(size_t capacity);

	void add(T* obj);
	void clear();
	bool isEmpty() const;

	size_t size() const;

	T*& operator[](int ind);
	const T* operator[](int ind) const;
};

template <class T>
void MyCollection<T>::free()
{
	for (int i = 0; i < _size; i++)
	{
		delete _data[i];
	}
	delete[] _data;
}

template <class T>
void MyCollection<T>::copyFrom(const MyCollection<T>& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = new T * [other._capacity];

	for (int i = 0; i < _size; i++)
	{
		_data[i] = other._data[i]->clone(); // T needs to have clone()
	}
}

template <class T>
void MyCollection<T>::moveFrom(MyCollection<T>&& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = other._data;

	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
}

template <class T>
void MyCollection<T>::resize(size_t newCapacity)
{
	if (newCapacity == 0) newCapacity = DEFAULT_CAPACITY;

	T** newCollection = new T * [newCapacity];
	for (int i = 0; i < _size; i++)
	{
		newCollection[i] = _data[i]; // we steal the pointers
	}
	delete[] _data;
	_capacity = newCapacity
	_data = newCollection;
}

template <class T>
MyCollection<T>::MyCollection(size_t capacity) : _size(0), _capacity(capacity)
{
	_data = new T * [capacity];
}

template <class T>
MyCollection<T>& MyCollection<T>::operator=(const MyCollection<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
MyCollection<T>& MyCollection<T>::operator=(MyCollection<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T>
MyCollection<T>::MyCollection(const MyCollection<T>& other)
{
	copyFrom(other);
}

template <class T>
MyCollection<T>::MyCollection(MyCollection<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <class T>
MyCollection<T>::~MyCollection()
{
	free();
}


template <class T>
size_t MyCollection<T>::size() const
{
	return _size;
}

template <class T>
T*& MyCollection<T>::operator[](int ind)
{
	if (ind >= _size)
		throw std::out_of_range("Index was out of range!");

	return _data[ind];
}

template <class T>
const T* MyCollection<T>::operator[](int ind) const
{
	if (ind >= _size)
		throw std::out_of_range("Index was out of range!");

	return _data[ind];
}

template <class T>
void MyCollection<T>::add(T* obj)
{
	if (_size == _capacity)
		resize(_capacity * 2);

	_data[_size++] = obj;
}

template <class T>
void MyCollection<T>::clear()
{
	for (int i = 0; i < _size; i++)
	{
		delete _data[i];
		_data[i] = nullptr
	}
	_size = 0;
}

template <class T>
bool MyCollection<T>::isEmpty() const
{
	return _size == 0;
}
