#pragma once
#include <iostream>

namespace
{
	const size_t INITIAL_CAPACITY = 8;
}

template <typename T>
class MyVector
{
	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;

	void resize(size_t newCapacity);

	void copyFrom(const MyVector<T>& other);
	void free();
	void moveFrom(MyVector<T>&& other);
public:
	MyVector() = default;
	MyVector(size_t capacity);
	MyVector(const MyVector<T>& other);
	MyVector<T>& operator=(const MyVector<T>& other);
	~MyVector();

	MyVector(MyVector<T>&& other);
	MyVector<T>& operator=(MyVector<T>&& other);

	void push_back(const T& obj);
	void push_back(T&& obj);

	void pop_back();

	void insert(unsigned index, const T& obj);
	void insert(unsigned index, T&& obj);

	void erase(unsigned index);

	bool empty() const;
	void clear();

	size_t size() const;

	T& operator[](size_t ind);
	const T& operator[](size_t ind) const;
};

/// BIG FOUR FUNCTIONS: 
template <typename T>
void MyVector<T>::copyFrom(const MyVector<T>& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = new T[_capacity];
	for (int i = 0; i < _size; i++)
	{
		_data[i] = other._data[i]; // T -> operator=
	}
}

template <typename T>
void MyVector<T>::free()
{
	delete[] _data;
	_data = nullptr;
	_size = 0;
}

template <typename T>
void MyVector<T>::moveFrom(MyVector<T>&& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = other._data;
	other._data = nullptr;
	other._capacity = 0;
	other._size = 0;
}


template <typename T>
MyVector<T>::MyVector(size_t capacity)
{
	_capacity = capacity;
	_data = new T[capacity];
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	copyFrom(other);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
MyVector<T>::~MyVector()
{
	free();
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other)
{
	moveFrom(other);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
void MyVector<T>::resize(size_t newCapacity)
{
	if (newCapacity == 0)
		newCapacity = INITIAL_CAPACITY; // on the initial resize, we set the capacity to 8


	T* temp = new T[newCapacity];

	for (int i = 0; i < _size; i++)
	{
		temp[i] = std::move(_data[i]); // we use the move operator, if T has one
	}
	delete[] _data;
	_data = temp;
}

/// FUNCTIONALITY:

template <typename T>
void MyVector<T>::push_back(const T& obj)
{
	if (_size == _capacity)
		resize(_capacity * 2);

	_data[_size++] = obj;
}

template <typename T>
void MyVector<T>::push_back(T&& obj)
{
	if (_size == _capacity)
		resize(_capacity * 2);

	_data[_size++] = std::move(obj);
}

template <typename T>
void MyVector<T>::pop_back()
{
	if (empty())
		throw std::logic_error("Vector is empty");

	_size--;
}

template <typename T>
bool MyVector<T>::empty() const
{
	return _size == 0;
}

template <typename T>
void MyVector<T>::clear()
{
	_size = 0;
}

template <typename T>
size_t MyVector<T>::size() const
{
	return _size;
}

template <typename T>
T& MyVector<T>::operator[](size_t ind)
{
	if (ind > _size)
		throw std::out_of_range("Index is out of range");

	return _data[ind];
}

template <typename T>
const T& MyVector<T>::operator[](size_t ind) const
{
	if (ind > _size)
		throw std::out_of_range("Index is out of range");

	return _data[ind];
}
template <typename T>
void MyVector<T>::insert(unsigned index, const T& obj)
{
	if (index >= _size)
		throw std::out_of_range("Index out of range");

	push_back(_data[_size - 1]); // we add the last element again, this ensures we have enough space and increments size

	for (int i = _size - 1; i > index; i--)
	{
		_data[i] = std::move(_data[i - 1]);
	}
	_data[index] = obj;
}
template <typename T>
void MyVector<T>::insert(unsigned index, T&& obj)
{
	if (index >= _size)
		throw std::out_of_range("Index out of range");

	push_back(_data[_size - 1]); 

	for (int i = _size - 1; i > index; i--)
	{
		_data[i] = std::move(_data[i - 1]);
	}
	_data[index] = std::move(obj);
}

template <typename T>
void MyVector<T>::erase(unsigned index)
{
	if (index >= _size)
		throw std::out_of_range("Index is out of range");
	_size--;
	for (int i = index; i < _size; i++) 
	{
		_data[i] = std::move(_data[i + 1]);
	}
}
