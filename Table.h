#pragma once
#include "Row.h"
#include "Utilities/MyVector.hpp"

class Table
{
	MyVector<Row> _rows;

	void readFromFile(const char* fileName);
	unsigned getLongestRowLenght() const;
public:
	Table(const char* fileName);

	void print() const;

	//to be removed
	void printTypes() const;
};

