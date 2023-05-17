#pragma once
#include "Row.h"


class Table
{
	MyVector<Row> _rows;
	size_t _rowsCount = 0;

	void readFromFile(const char* fileName);

public:
	Table(const char* fileName);

	void print() const;

	//to be removed
	void printTypes() const;
};

