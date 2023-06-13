#pragma once
#include <iostream>
#include "Cell.h"

class CellEmpty : public Cell
{
public:
	CellEmpty() = default;

	void printCell(size_t len, std::ostream& os) const override;

	Cell* clone() const override;

	double evaluate() const override;
};
