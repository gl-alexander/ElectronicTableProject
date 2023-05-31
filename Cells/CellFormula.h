#pragma once
#include <iostream>
#include "Cell.h"
#include "../MyVector.hpp"

class CellFormula : public Cell
{
	//stack of cells
	//stack of operators
	MyVector<Cell> _cells;
	MyVector<char> _operators;

	Cell* _left;
	Cell* _right;
public:
	CellFormula();

	void printCell(size_t len) const override;

	Cell* clone() const override;

	void setValue(const MyString& value);

	double getValue() const;
};

