#pragma once
#include "Row.h"
#include "Utilities/MyVector.hpp"
#include "Factory/ExpressionFactory.h"


class Table
{
	MyVector<Row> _rows;


	void readFromFile(const char* fileName);
	unsigned getLongestRowLenght() const;
	unsigned getLongestCell() const;
	void parseFormula(CellFormula* cf);
public:
	Table(const char* fileName);

	void print(std::ostream& os) const;

	const Cell* getCellByLocation(size_t x, size_t y) const;

	void parseFromulas();

	//to be removed
	void printTypes() const;
};

