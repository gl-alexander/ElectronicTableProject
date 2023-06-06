#pragma once
#include "Cell.h"
#include "Utilities/MyCollection.hpp"
#include <fstream>

class Row
{
	MyCollection<Cell> _cells;

public:
	Row() = default;
	Row(std::ifstream& ifs);

	void readRowFromFile(std::ifstream& ifs);

	Cell& operator[](int ind);
	const Cell& operator[](int ind) const;

	unsigned lenght() const;
	void printRow(size_t margin) const;

	//to be removed:
	void printValueTypes() const;
};

