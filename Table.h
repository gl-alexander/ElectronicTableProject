#pragma once
#include "Row.h"
#include "Utilities/MyVector.hpp"
#include "Factory/ExpressionFactory.h"


class Table
{
	MyString _filePath;
	MyVector<Row> _rows;


	void readFromFile(const MyString& fileName);
	unsigned getLongestRowLenght() const;
	unsigned getLongestCell() const;
	void parseFormula(CellFormula* cf);
	void parseFromulas();

	void editExistingCell(size_t row, size_t col, const MyString& newValue);
	void addNewCell(size_t row, size_t col, const MyString& newValue);

	void editSameType(Cell* cell, const MyString& newValue);
public:
	Table(const MyString& fileName);

	void print(std::ostream& os) const;

	const Cell* getCellByLocation(size_t x, size_t y) const;

	void saveToFile(const MyString& filePath) const;

	const MyString& getTableFilePath() const;

	void editCell(const MyString& cellLocation, const MyString& newValue);

	//to be removed
	void printTypes() const;
};

