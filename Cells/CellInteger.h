#pragma once
#include <iostream>
#include "Cell.h"

class CellInteger : public Cell
{
	int _value = 0;
public:
	CellInteger() = default;

	CellInteger(int value);

	void printCell(size_t len, std::ostream& os) const override;

	Cell* clone() const override;

	void setValue(int value);

	int getValue() const;

	double evaluate() const override;
};
