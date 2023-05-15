#pragma once
#include "Row.h"


class Table
{
	Row* _rows = nullptr;
	size_t _rowsCount = 0;

	void copyFrom(const Table& other);
	void free();
	void moveFrom(Table&& other);

	void readFromFile(const char* fileName);
public:
	Table() = default;
	Table(const Table& other);
	Table& operator=(const Table& other);
	~Table() noexcept;

	Table(Table&& other) noexcept;
	Table& operator=(Table&& other) noexcept;

	Table(const char* fileName);

	void print() const;


};

