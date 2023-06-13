#pragma once
#include <iostream>
#include "Cell.h"

class CellFraction : public Cell
{
	double _value;
public:
	CellFraction() = default;

	CellFraction(double value);

	void printCell(size_t len, std::ostream& os) const override;

	Cell* clone() const override;

	void setValue(double value);

	double getValue() const;

	double evaluate() const override;
};

