#pragma once
#include "Cell.h"
#include "MyVector.hpp"
#include <fstream>

class Row
{
	MyVector<Cell> _cells;
	size_t _cellCount = 0;

public:
	Row() = default;
	Row(std::ifstream& ifs);

	void readRowFromFile(std::ifstream& ifs);

	Cell& operator[](int ind);
	const Cell& operator[](int ind) const;

	//to be removed:
	void printValueTypes() const;
};

