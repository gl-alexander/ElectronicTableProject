#pragma once

template <typename T> 
class MyVector
{
	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;

	void copyFrom(const MyVector& other);
	void free();
	void moveFrom(MyVector&& other);
public:
	MyVector<T>() = default;
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);
	~MyVector();

	MyVector(MyVector&& other);
	MyVector& operator=(MyVector&& other);

	void push_back(const T& obj);
	void push_back(T&& obj);

	void pop_back();

	bool empty() const;
	void clear();
	
	size_t size() const;

	T& operator[](size_t ind);
	const T& operator[](size_t ind) const;
};
