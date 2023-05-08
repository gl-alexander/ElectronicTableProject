#pragma once
#include "Row.h"


class Table
{
	Row* _rows = nullptr;
	size_t _rowsCount = 0;

	void copyFrom(const Table& other);
	void free();
	void moveFrom();

	void readFromFile(const char* fileName);
public:
	Table() = default;
	Table(const Table& other);
	Table& operator=(const Table& other);
	~Table();

	Table(Table&& other);
	Table& operator=(Table&& other);

	Table(const char* fileName);

	void print() const;

};

