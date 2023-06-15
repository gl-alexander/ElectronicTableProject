#pragma once
#include "Row.h"
#include "Utilities/MyVector.hpp"
#include "Factory/ExpressionFactory.h"


class Table
{
	MyString filePath;
	MyVector<Row> _rows;


	void readFromFile(const MyString& fileName);
	unsigned getLongestRowLenght() const;
	unsigned getLongestCell() const;
	void parseFormula(CellFormula* cf);
	void parseFromulas();
public:
	Table(const MyString& fileName);

	void print(std::ostream& os) const;

	const Cell* getCellByLocation(size_t x, size_t y) const;

	void saveToFile(const MyString& filePath) const;

	//to be removed
	void printTypes() const;
};

