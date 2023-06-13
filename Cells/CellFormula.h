#pragma once
#include <iostream>
#include "Cell.h"
#include "../Utilities/MyVector.hpp"

class CellFormula : public Cell
{
	//stack of cells
	//stack of operators
	MyString _expression;

	MyVector<Cell> _cells;
	MyVector<char> _operators;

	Cell* _left;
	Cell* _right;
public:
	CellFormula() = default;

	CellFormula(const MyString& expression);

	void printCell(size_t len, std::ostream& os) const override;

	Cell* clone() const override;

	void setValue(const MyString& value);

	void parseInput(std::stringstream& ss);

	double evaluate() const override;

	double getValue() const;
};

