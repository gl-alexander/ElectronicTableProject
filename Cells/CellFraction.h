#pragma once
#include <iostream>
#include "Cell.h"

class CellFraction : public Cell
{
	double _value;
public:
	CellFraction();

	void printCell(size_t len) const override;

	Cell* clone() const override;

	void setValue(double value);

	double getValue() const;
};

